#ifndef RECTANGLERECOGNIZER_H
#define RECTANGLERECOGNIZER_H

#include <rectanglerecognizer_global.h>

#include <QObject>
#include <QString>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

#include <plugin_interfaces.h>

class RECTANGLERECOGNIZERSHARED_EXPORT RectangleRecognizer :
        public QObject,
        public IVerbosePlugin,
        public ITestMethod
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "PatternRecognizer.RectangleRecognizer")
    Q_INTERFACES(IVerbosePlugin ITestMethod)
public:
    RectangleRecognizer() { }
    virtual QString getShape() const {
        return "rectangle";
    }
    virtual QString getDescription() const {
        return "Use Canny + dilate, use findCountour on different colors, use approxPolyDP() etc...";
    }
    virtual int successPercentage() const {
        return 10;
    }
    virtual void testMethod(cv::Mat& image, std::vector<std::vector<cv::Point>>& contours) {
        contours.clear();
        cv::Mat pyr, timg, gray0(image.size(), CV_8U), gray;

        cv::pyrDown(image, pyr, cv::Size(image.cols/2, image.rows/2));
        cv::pyrUp(pyr, timg, image.size());

        for( int c = 0; c < 3; c++ ) {
            int ch[] = {c, 0};
            cv::mixChannels(&timg, 1, &gray0, 1, ch, 1);
            for( int l = 0; l < 11; l++ ) {
                if( l == 0 ) {
                    cv::Canny(gray0, gray, 0, 50, 5);
                    cv::dilate(gray, gray, cv::Mat(), cv::Point(-1,-1));
                } else {
                    gray = gray0 >= (l+1)*255/11;
                }

                std::vector<std::vector<cv::Point>> temp;
                cv::findContours(gray, temp, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
                std::vector<cv::Point> approx;
                for( size_t i = 0; i < temp.size(); i++ ) {
                    cv::approxPolyDP(cv::Mat(temp[i]), approx, cv::arcLength(cv::Mat(temp[i]), true)*0.02, true);
                    if( approx.size() == 4 &&
                        fabs(cv::contourArea(cv::Mat(approx))) > 1000 &&
                        cv::isContourConvex(cv::Mat(approx)) )
                    {
                        double maxCosine = 0;
                        for( int j = 2; j < 5; j++ ) {
                            double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                            maxCosine = MAX(maxCosine, cosine);
                        }
                        if( maxCosine < 0.3 )
                            contours.push_back(approx);
                    }
                }
            }
        }
    }

private:

    static double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 )
    {
        double dx1 = pt1.x - pt0.x;
        double dy1 = pt1.y - pt0.y;
        double dx2 = pt2.x - pt0.x;
        double dy2 = pt2.y - pt0.y;
        return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
    }
};

#endif // RECTANGLERECOGNIZER_H
