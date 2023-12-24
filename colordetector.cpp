#include "colordetector.h"

//empty constructor
ColorDetector::ColorDetector():minDist(100){
    target[0] = target[1] = target[2] = 0;
}

void ColorDetector::setColorDistanceThreshold(int distance){
    if(distance < 0){
        distance = 0;
    }
    minDist = distance;
}

void ColorDetector::setTargetColor(unsigned char red,
                                   unsigned char green,
                                   unsigned char blue){
    //BGR order
    target[2] = red;
    target[1] = green;
    target[0] = blue;
}


void ColorDetector::setTargetColor(cv::Vec3b color){
    target = color;
}

int ColorDetector::getColorDistanceThreshold() const{
    return minDist;
}

cv::Vec3b ColorDetector::getTargetColor() const{
    return target;
}

cv::Mat ColorDetector::process(const cv::Mat &img){
    // re-allocate binary map if necessary
    result.create(img.rows,img.cols,CV_8U);
    cv::Mat_<cv::Vec3b>::const_iterator it = img.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itend = img.end<cv::Vec3b>();
    cv::Mat_<uchar>::iterator itout = result.begin<uchar>();

    for(;it!=itend; ++it, ++itout){
        //process each pixel
        if(getDistance(*it)<minDist){
            *itout = 255;
        }else{
            *itout = 0;
        }
    }
    return result;
}
