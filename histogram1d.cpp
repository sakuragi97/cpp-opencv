#include "histogram1d.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>


Histogram1D::Histogram1D()
{
// Prepare argument of 1D histogram
    histSize[0] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    channels[0] = 0; //by default, look at channel 0

}


cv::MatND Histogram1D::getHistogram(const cv::Mat &img){
    cv::MatND hist;
    cv::calcHist(&img,
                 1,         // histogram from 1 image only
                 channels, // the channel used
                 cv::Mat(), // no mask is used
                 hist,      // the resulting histogram
                 1,         // it is a 1D histogram
                 histSize, // number of bins
                 ranges     // pixel value range
                 );
    return hist;
}


cv::Mat Histogram1D::getHistogramImage(const cv::Mat &img){

    // Compute histogram first
    cv::MatND hist = getHistogram(img);

    // Get min and max bin values
    double maxVal = 0;
    double minVal = 0;
    cv::minMaxLoc(hist,&minVal,&maxVal,0,0);

    //Image on which to display histogram

    cv::Mat histImg(histSize[0], histSize[0], CV_8U, cv::Scalar(255));

    // set highest point at 90% of nbins
    int hpt = static_cast<int>(0.9*histSize[0]);

    // Draw a vertical line for each bin
    for(int i=0; i<histSize[0]; i++){
        float binVal = hist.at<float>(i);
        int intensity = static_cast<int>(binVal*hpt/maxVal);

        // This function draws a line between 2 points
        cv::line(histImg, cv::Point(i,histSize[0]),
                 cv::Point(i,histSize[0]-intensity),
                 cv::Scalar::all(0) );
    }
    return histImg;
}

cv::Mat Histogram1D::applyLookUp(const cv::Mat &img, const cv::Mat &lookup){
    cv::Mat result;
    cv::LUT(img,lookup,result);
    return result;
}

cv::Mat Histogram1D::equalize(const cv::Mat &img){
    cv::Mat result;
    cv::equalizeHist(img,result);
    return result;
}

cv::Mat Histogram1D::getCalcBackProject(const cv::Mat &img, const cv::Mat &ROI){
    cv::Mat result;
    Histogram1D h;
    cv::MatND hist = h.getHistogram(ROI);
    cv::normalize(hist,hist,1.0);
    cv::calcBackProject(&img,1,channels,hist,result,ranges,255.0);
    return result;
}

