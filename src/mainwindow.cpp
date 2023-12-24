#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/colordetectorcontroller.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QFileDialog>
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->processButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "C:\\Dev\\C++\\opencvProject\\opencvProject\\data",
                                            tr("Image Files (*.png *.jpg *.bmp)"));

    img = cv::imread(fileName.toStdString().data());
    if(img.data){
        ui->processButton->setEnabled(true);
    }
}

// Add white noise to the image
void saltImage(cv::Mat &img, int n){
    for(int k=0; k<n;k++){
        int i = rand() % img.rows;
        int j = rand() % img.cols;
        if(img.channels() == 1){
            img.at<uchar>(i,j) = 255;
        }else if(img.channels()==3){
            img.at<cv::Vec3b>(i,j)[0] = 255;
            img.at<cv::Vec3b>(i,j)[1] = 255;
            img.at<cv::Vec3b>(i,j)[2] = 255;
        }
    }
}

void colorReduce(cv::Mat &img, int div=64){
    int nl = img.rows; //number of lines
    int nc = img.cols * img.channels(); //total number of elements per line

    for(int i=0; i<nl;i++){
        uchar* data = img.ptr<uchar>(i); //get the adress of row i
        for(int j=0; j<nc;j++){
            data[j] = data[j]/div*div + div/2; //process each pixel
        }
    }
}

void colorReduceIt(cv::Mat &img, int div=64){
    cv::MatIterator_<cv::Vec3b> it = img.begin<cv::Vec3b>();
    cv::MatIterator_<cv::Vec3b> itend = img.end<cv::Vec3b>();
    while(it!=itend){
        (*it)[0] = (*it)[0]/div*div + div/2;
        (*it)[1] = (*it)[1]/div*div + div/2;
        (*it)[2] = (*it)[2]/div*div + div/2;
        ++it;
    }
}

void colorReduceFastest(cv::Mat &img, int div=64){
    int nl = img.rows;
    int nc = img.cols * img.channels();

    if(img.isContinuous()){ //Check if the img is padded (optimized matrix)
        nc = nc*nl;
        nl = 1; //1D array
    }
    for(int i=0;i<nl;++i){
        uchar* data = img.ptr<uchar>(i);
        for(int j=0;j<nc;++j){
            data[j] = data[j]/div*div + div/2;
        }
    }
}

//Native Sharpen
void sharpen(cv::Mat &img, cv::Mat &result){
    //cv::cvtColor(img,img,cv::COLOR_BGR2GRAY); // the logic below considering the image grayscale
    result.create(img.size(), img.type()); //optional to allocate space (recommanded)
    for (int i=1; i<img.rows-1;i++){
        const uchar* previous = img.ptr<const uchar>(i-1);
        const uchar* current = img.ptr<const uchar>(i);
        const uchar* next = img.ptr<const uchar>(i+1);
        uchar* output = result.ptr<uchar>(i);

        for (int j=1; j<img.cols-1;j++){
            *output++= cv::saturate_cast<uchar>(5*current[j]-current[j-1]-current[j+1]-previous[j]-next[j]);
        }
    }
    //Set the unprocessed pixel to 0
    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));
}

//Sharpen using kernels -> filter2d
void sharpenKernel(cv::Mat &img, cv::Mat &result){
    cv::Mat kernel(3,3, CV_32F, cv::Scalar(0));
    kernel.at<float>(1,1) = 5.0;
    kernel.at<float>(0,1) = -1.0;
    kernel.at<float>(1,0) = -1.0;
    kernel.at<float>(2,1) = -1.0;
    kernel.at<float>(1,2) = -1.0;

    cv::filter2D(img,result,img.depth(),kernel);
}

//Apply arithmetic operator to an image
void channelSaturation(cv::Mat &img, cv::Mat &result){
    result.create(img.size(), img.type());
    cv::add(img,cv::Scalar(-10,-10,50),result); //Make the image more Redish
}


//Splitting the image channels
//// create vector of 3 images
//std::vector<cv::Mat> planes;
//// split 1 3-channel image into 3 1-channel images
//cv::split(image1,planes);
//// add to blue channel
//planes[0]+= image2;
//// merge the 3 1-channel images into 1 3-channel image
//cv::merge(planes,result);


//ROI - Region of Interest
void addImage(cv::Mat &img, cv::Mat &img2){
    cv::Mat imgROI = img(cv::Rect(50,50,img2.cols,img2.rows));
    cv::addWeighted(imgROI,1.0,img2,1.0,0.,imgROI);
}

void MainWindow::on_processButton_clicked()
{
    //saltImage(img,3000);
    //colorReduceIt(img);
    //colorReduceFastest(img);
    cv::Mat output;
    //sharpenKernel(img,output);
    //channelSaturation(img,output);
    //std::string path = "C:\\Users\\User\\Documents\\opencvQt5Project\\data\\alert.png";
    //cv::Mat img2 = cv::imread(path);
    //cv::resize(img2,output,cv::Size(),0.5,0.5);
    //addImage(img,output);

    //Color Detector Class exmaple
//    ColorDetector colordetector;
//    colordetector.setTargetColor(224,172,105); //Skin Color

    //cv::imshow("Image processed", colordetector.process(img));


    ColorDetectorController::getInstance()->setColorDistanceThreshold(
        ui->horizontalSlider->value());
    ColorDetectorController::getInstance()->setInputImage(img);
    ColorDetectorController::getInstance()->process();
    output = ColorDetectorController::getInstance()->getLastResult();

//    cv::cvtColor(img,img,cv::COLOR_BGR2RGB);
//    QImage Qimg = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
    QImage Qimg = QImage((const unsigned char*)(output.data),output.cols,output.rows,QImage::Format_Grayscale8);
    ui->imgLabel->setPixmap(QPixmap::fromImage(Qimg));
    ui->imgLabel->resize(ui->imgLabel->size());
}


void MainWindow::on_selectColorButton_clicked()
{

    QColor color = QColorDialog::getColor(Qt::green, this);
    if (color.isValid()) {
        ColorDetectorController::getInstance()->setTargetColor(color.red(),color.green(),color.blue());
    }

}

