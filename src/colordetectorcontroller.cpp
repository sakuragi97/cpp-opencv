#include "colordetectorcontroller.h"
#include <opencv2/highgui/highgui.hpp>


ColorDetectorController::ColorDetectorController(){
    colordetector = new ColorDetector();
}

ColorDetectorController::~ColorDetectorController() {
    delete colordetector;
}


void ColorDetectorController::setColorDistanceThreshold(int distance){
    colordetector->setColorDistanceThreshold(distance);
}

int ColorDetectorController::getColorDistanceThreshold() const{
    return colordetector->getColorDistanceThreshold();
}

void ColorDetectorController::setTargetColor(unsigned char red, unsigned char green, unsigned char blue){
    colordetector->setTargetColor(red,green,blue);
}

void ColorDetectorController::getTargetColor(unsigned char &red, unsigned char &green, unsigned char &blue) const{
    cv::Vec3b color = colordetector->getTargetColor();
    red = color[2];
    green = color[1];
    blue = color[0];
}

bool ColorDetectorController::setInputImage(std::string filename){
    img = cv::imread(filename);
    if(!img.data){
        return false;
    }else{
        return true;
    }
}

bool ColorDetectorController::setInputImage(cv::Mat image){
    if(!image.data){
        return false;
    }else{
    img = image;
        return true;
    }
}
const cv::Mat ColorDetectorController::getInputImage() const{
    return img;
}

void ColorDetectorController::process(){
    result = colordetector->process(img);
}
const cv::Mat ColorDetectorController::getLastResult() const{
    return result;
}

ColorDetectorController *ColorDetectorController::singleton=0;


ColorDetectorController *ColorDetectorController::getInstance(){
    if(singleton == 0){
        singleton = new ColorDetectorController;
    }
    return singleton;
}

void ColorDetectorController::destroy(){
    if(singleton!=0){
        delete singleton;
        singleton = 0;
    }
}
