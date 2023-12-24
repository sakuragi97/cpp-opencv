#ifndef HISTOGRAM1D_H
#define HISTOGRAM1D_H

#include <opencv2/core/core.hpp>

class Histogram1D
{
public:
    Histogram1D();
    cv::MatND getHistogram(const cv::Mat &img);
    cv::Mat getHistogramImage(const cv::Mat &img); // Computes the 1D histogram and returns an image of it.
    cv::Mat applyLookUp(const cv::Mat &img, const cv::Mat &lookup);
    cv::Mat equalize(const cv::Mat &img);
    cv::Mat getCalcBackProject(const cv::Mat &img, const cv::Mat &ROI);

private:
    int histSize[1]; //number of bins
    float hranges[2]; //min an max pixel values
    const float* ranges[1]; //store the hranges
    int channels[1]; //1D channel - grayscale

};

#endif // HISTOGRAM1D_H
