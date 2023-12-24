#include "morphofeatures.h"


MorphoFeatures::MorphoFeatures()
{

}


cv::Mat MorphoFeatures::getEdges(const cv::Mat &img){
    //Get the gradient image
    cv::Mat result;
    cv::morphologyEx(img,result,cv::MORPH_GRADIENT,cv::Mat());

    //Apply threshold to obtain a binary image
    applyThreshold(result);
    return result;

}

void MorphoFeatures::applyThreshold(const cv::Mat &img){
    if(threshold>0){
        cv::threshold(img,img,threshold,255,cv::THRESH_BINARY);
    }
}

int MorphoFeatures::getThreshold() const
{
    return threshold;
}

void MorphoFeatures::setThreshold(int newThreshold)
{
    threshold = newThreshold;
}
