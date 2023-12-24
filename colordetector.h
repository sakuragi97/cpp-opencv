#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H
#include <opencv2/core/core.hpp>
#include <cstdlib>

class ColorDetector
{
public:
    ColorDetector();
    void setColorDistanceThreshold(int distance);
    int getColorDistanceThreshold() const;
    void setTargetColor(unsigned char red,
                        unsigned char green,
                        unsigned char blue);
    void setTargetColor(cv::Vec3b color);
    cv::Vec3b getTargetColor() const;

    cv::Mat process(const cv::Mat &img);

private:
    // minimum acceptable distance
    int minDist;
    // target color
    cv::Vec3b target;
    // image containing resulting imaging map
    cv::Mat result;

    // compute distance from target color
    int getDistance(const cv::Vec3b &color) const{
        return abs(color[0] - target[0])+abs(color[1] - target[1])+abs(color[2] - target[2]);
    }
};

#endif // COLORDETECTOR_H
