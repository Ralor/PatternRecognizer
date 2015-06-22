#ifndef TRIANGLERECOGNIZER_H
#define TRIANGLERECOGNIZER_H

#include "trianglerecognizer_global.h"

#include <QObject>
#include <QString>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

#include <plugin_interfaces.h>


class TRIANGLERECOGNIZERSHARED_EXPORT TriangleRecognizer :
        public QObject,
        public IVerbosePlugin,
        public ITestMethod
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "PatternRecognizer.TriangleRecognizer" FILE "trianglerecognizer.json")
    Q_INTERFACES(IVerbosePlugin ITestMethod)
public:
    TriangleRecognizer() { }
    virtual QString getShape() const {
        return "triangle";
    }
    virtual QString getDescription() const {
        return "use Canny, ";
    }
    virtual int successPercentage() const {
        return 40;
    }
    virtual void testMethod(cv::Mat& image, std::vector<std::vector<cv::Point>>& contours) {
        cv::Mat img_gray;
        cv::cvtColor(image, img_gray, CV_RGB2GRAY);

        const int thresh = 100;
        cv::Mat canny_output;
        cv::Canny(img_gray, canny_output, thresh, 3 * thresh, 3);

        std::vector<std::vector<cv::Point>> temp_contours;
        std::vector<cv::Vec4i> hierarchy;
        findContours(canny_output, temp_contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

        contours.clear();
        for(std::vector<cv::Point>& contour : temp_contours) {
            std::vector<cv::Point> approxTriangle;
            cv::approxPolyDP(contour, approxTriangle, cv::arcLength(cv::Mat(contour), true)*0.05, true);
            if( approxTriangle.size() == 3 )
                contours.push_back(approxTriangle);
        }
    }
};

#endif // TRIANGLERECOGNIZER_H
