#ifndef COLORDETECTORCONTROLLER_H
#define COLORDETECTORCONTROLLER_H
#include "colordetector.h"


class ColorDetectorController
{
public:

    void setColorDistanceThreshold(int distance);
    int getColorDistanceThreshold() const;
    void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
    void getTargetColor(unsigned char &red, unsigned char &green, unsigned char &blue) const;
    bool setInputImage(std::string filename);
    bool setInputImage(cv::Mat img);

    const cv::Mat getInputImage() const;
    void process();
    const cv::Mat getLastResult() const;

    static ColorDetectorController *getInstance();


    static void destroy();


private:
    ColorDetector *colordetector;
    cv::Mat img; // the image to be processed
    cv::Mat result; // the result

    //Singleton Design Pattern
    ColorDetectorController();

    ~ColorDetectorController();

    static ColorDetectorController *singleton;



};

#endif // COLORDETECTORCONTROLLER_H
