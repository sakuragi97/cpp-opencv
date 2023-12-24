#include "headers/mainwindow2.h"
#include "ui_mainwindow2.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QFileDialog>
#include "headers/histogram1d.h"
#include "headers/morphofeatures.h"
#include <iostream>

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::on_openImageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "C:\\Dev\\C++\\opencvProject\\opencvProject\\data",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));

    img = cv::imread(fileName.toStdString().data());
    if(img.data){
        ui->processButton->setEnabled(true);
    }

    cv::Mat cvtImg;
    cvtImg.create(img.size(), img.type());
    cv::cvtColor(img,cvtImg,cv::COLOR_BGR2GRAY);

    QImage Qimg = QImage((const unsigned char*)(cvtImg.data),cvtImg.cols,cvtImg.rows,QImage::Format_Grayscale8);
    ui->imgLabel->setPixmap(QPixmap::fromImage(Qimg));
    ui->imgLabel->resize(ui->imgLabel->size());
}


void MainWindow2::on_processButton_clicked()
{
    Histogram1D h;
    cv::Mat cvtImg;
    //Compute the histogram
    if(img.channels() == 3){
        cv::cvtColor(img,cvtImg,cv::COLOR_BGR2GRAY);
    }
/*
    cv::MatND hist = h.getHistogram(cvtImg);

    for(int i=0; i<256; i++){
        std::cout << "Value " << i << ": " << hist.at<float>(i) << std::endl;
    }
*/
/*
    cv::Mat hist = h.getHistogramImage(cvtImg);
    cv::imshow("Image Histogram", hist);
*/
/*
    int dim = 256;
    cv::Mat lookup(1,&dim, CV_8U);
    for(int i=0;i<256;i++){
        lookup.at<uchar>(i) = 255-i;
    }

    cv::Mat output = h.applyLookUp(cvtImg,lookup);
*/
/*
    cv::Mat output = h.equalize(cvtImg);
    cv::imshow("Image Output", output);
    cv::imshow("Image Input Histogram", h.getHistogramImage(cvtImg));
    cv::imshow("Image Output Histogram", h.getHistogramImage(output));
*/
/*
    cv::Mat ROI;
    ROI = cvtImg(cv::Rect(400,100,100,100));

    cv::Mat result = h.getCalcBackProject(img,ROI);
    cv::threshold(result,result, 255*0.15,255,cv::THRESH_BINARY);
    cv::imshow("Image Output",result);
//    cv::imshow("Image Output Histogram", h.getHistogramImage(ROI));
*/


// Morphological Operations
/*
    // Erode the image
    cv::Mat erodedImg;
    cv::threshold(cvtImg,cvtImg,150,255,cv::THRESH_BINARY);
    cv::erode(cvtImg,erodedImg,cv::Mat());

    cv::imshow("Image Input", cvtImg);
    cv::imshow("Image Eroded", erodedImg);

    //Dilate the image
    cv::Mat dilatedImg;
    cv::dilate(cvtImg,dilatedImg,cv::Mat());
    cv::imshow("Image Dilated", dilatedImg);
*/

    //Detecting edges with morphological filters
    MorphoFeatures morpho;
    morpho.setThreshold(40);

    //Get the edges
    cv::Mat edges;
    edges = morpho.getEdges(cvtImg);
    cv::imshow("Detected Edges", edges);

}

