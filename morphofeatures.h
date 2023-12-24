#ifndef MORPHOFEATURES_H
#define MORPHOFEATURES_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class MorphoFeatures
{
public:
    MorphoFeatures();
    cv::Mat getEdges(const cv::Mat &img);
    void applyThreshold(const cv::Mat &img);


    int getThreshold() const;
    void setThreshold(int newThreshold);

private:
    int threshold; // to produce binary image

    // structuring elements used in corner detection
    cv::Mat square;
    cv::Mat cross;
    cv::Mat diamond;
    cv::Mat x;
};

#endif // MORPHOFEATURES_H
