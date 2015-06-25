#ifndef PLUGIN_INTERFACES_H
#define PLUGIN_INTERFACES_H

#include <QtPlugin>
#include <QString>

#include <opencv2/imgproc.hpp>
#include <vector>

class IVerbosePlugin {
public:
    virtual ~IVerbosePlugin() { }
    virtual QString getShape() const = 0;
    virtual QString getDescription() const = 0;
    virtual int successPercentage() const = 0;
};
#define IVerbosePlugin_iid "PatternRecognizer.IVerbosePlugin"
Q_DECLARE_INTERFACE(IVerbosePlugin, IVerbosePlugin_iid)

// There can be any further improvements like IWiseWorkMaker or mb ICannyTresholder.
// Interfaces are named by used approach.

// ITestMethod is just copy-paste from www.
class ITestMethod {
public:
    virtual ~ITestMethod() { }
    virtual void testMethod(cv::Mat& image, std::vector<std::vector<cv::Point>>& contours) = 0;
};
#define ITestMethod_iid "PatternRecognizer.ITestMethod"
Q_DECLARE_INTERFACE(ITestMethod, ITestMethod_iid)

#endif // PLUGIN_INTERFACES_H
