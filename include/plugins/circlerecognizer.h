#ifndef CIRCLERECOGNIZER_H
#define CIRCLERECOGNIZER_H

#include <circlerecognizer_global.h>

#include <QObject>
#include <QString>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

#include <plugin_interfaces.h>

class CIRCLERECOGNIZERSHARED_EXPORT CircleRecognizer :
        public QObject,
        public IVerbosePlugin,
        public ITestMethod
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "PatternRecognizer.RectangleRecognizer")
    Q_INTERFACES(IVerbosePlugin ITestMethod)
public:
    CircleRecognizer() { }
    virtual QString getShape() const {
        return "circle";
    }
    virtual QString getDescription() const {
        return "Use Canny on grayscale image ...";
    }
    virtual int successPercentage() const {
        return 10;
    }
    virtual void testMethod(cv::Mat& image, std::vector<std::vector<cv::Point>>& contours) {
        contours.clear();
        cv::Mat bin(image.size(), CV_8U);
        cv::cvtColor(image,bin,CV_BGR2GRAY);
        cv::Mat canny_output;
        cv::Canny(bin,canny_output,50,200);
        std::vector<std::vector<cv::Point>> temp;
        cv::findContours(canny_output, temp, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
        for(size_t i = 0; i < temp.size(); i++) {
            double area = cv::contourArea(cv::Mat(temp[i]));
            double perim = cv::arcLength(cv::Mat(temp[i]), true);
            if ( area / (perim * perim) > 0.07 && area / (perim * perim)< 0.087 ){
                contours.push_back(temp[i]);
            }
        }
    }
};

#endif // CIRCLERECOGNIZER_H
