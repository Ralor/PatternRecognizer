#ifndef CVIMAGEWIDGET_H
#define CVIMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QObject>
#include <QPluginLoader>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <vector>

#include <plugins/plugin_interfaces.h>
#include <plugins/pluginmanager.h>

class CVImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CVImageWidget(QWidget *parent = 0)
        : QWidget(parent),
          pluginShapeName_(""),
          plugin_(nullptr),
          qpen_(QPen(QColor(255,0,0))),
          img_set_(false),
          plugin_set_(false),
          contours_set_(false)
        {}

    QSize sizeHint() const { return qimage_.size(); }
    QSize minimumSizeHint() const { return qimage_.size(); }
    QString errorString() const { return errbuf_; }
    unsigned shapesCount() const { return contours_.size(); }
    QString getPluginShape() const {
        IVerbosePlugin* info;
        if( plugin_ && (info = qobject_cast<IVerbosePlugin*>(plugin_)) ) {
            return info->getShape();
        }
        return "null";
    }
    QString getPluginDescription() const {
        IVerbosePlugin* info;
        if( plugin_ && (info = qobject_cast<IVerbosePlugin*>(plugin_)) ) {
            return info->getDescription();
        }
        return "null";
    }
    QString getPluginSuccessPercentage() const {
        IVerbosePlugin* info;
        if( plugin_ && (info = qobject_cast<IVerbosePlugin*>(plugin_)) ) {
            return QString::number(info->successPercentage());
        }
        return "null";
    }

public slots:

    bool loadPlugin(const QString& filePath) {
        // copy dll to ../bin/
        QString fileName = QFileInfo(filePath).fileName();
        QFile::copy(filePath, "../bin/" + fileName);

        loader_.setFileName(filePath);
        QObject* plugin;
        if( plugin_ != nullptr && !loader_.unload() ) {
            qDebug() << "Prevous plugin can't be unloaded!";
            qDebug() << "---> " << loader_.errorString();
        }
        if( loader_.load() && (plugin = loader_.instance()) ) {
            qDebug() << filePath << " successfuly loaded.";
            IVerbosePlugin* info;
            if( info = qobject_cast<IVerbosePlugin*>(plugin) ) {
                qDebug() << "Shape: " << info->getShape();
                qDebug() << "Descr: " << info->getDescription();
                qDebug() << "Quality: " << info->successPercentage() << "\%";
                pluginShapeName_ = info->getShape();
            } else {
                errbuf() = "Plugin \"" + fileName + "\" is unsafe since it don't have any info included!";
                return false;
            }
            plugin_ = plugin;
            plugin_set_ = true;
            return true;
        }
        errbuf() = "Can't load " + filePath + "! " + loader_.errorString();
        return false;
    }

    bool showImage(const QString& fileName) {
        cv::Mat image = cv::imread(fileName.toStdString());
        if( image.empty() ) {
            errbuf() = "File " + fileName + "can't be loaded!";
            return false;
        }
        setQImage(image);
        img_set_ = true;
        contours_set_ = false;
        contours_.clear();
        repaint();
        return true;
    }
    bool paintContours() {
        if( img_set_ && plugin_set_ && setContours(img_) ) {
            repaint();
            return true;
        }
        errbuf() = "Make sure you have plugin and image opened";
        return false;
    }
    void setPenColor(const QColor& color) {
        qpen_.setColor(color);
    }
    void setPenWidth(const int& width) {
        qpen_.setWidth(width);
    }

protected:

    bool setContours(cv::Mat& image) {
       if( ITestMethod* interface = qobject_cast<ITestMethod*>(plugin_) ) {
           interface->testMethod(image, contours_);
           contours_set_ = true;
           return true;
       }
       qDebug() << "Can't qobject_cast plugin to ITestMethod!";
       return false;
    }

    void setQImage(const cv::Mat& image) {
        // Convert the image to the RGB888 format
        switch (image.type()) {
        case CV_8UC1:
            cv::cvtColor(image, img_, CV_GRAY2RGB);
            break;
        case CV_8UC3:
            cv::cvtColor(image, img_, CV_BGR2RGB);
            break;
        }
        // QImage needs the data to be stored continuously in memory
        assert(img_.isContinuous());
        // Assign OpenCV's image buffer to the QImage. Note that the bytesPerLine parameter
        // (http://qt-project.org/doc/qt-4.8/qimage.html#QImage-6) is 3*width because each pixel
        // has three bytes.
        qimage_ = QImage(img_.data, img_.cols, img_.rows, img_.cols*3, QImage::Format_RGB888);

        //this->setFixedSize(qimage_.size().width(), qimage_.size().height());
    }

    void paintEvent(QPaintEvent* /*event*/) {
        QPainter painter(this);
        painter.setPen(qpen_);

        // Display the image
        double scaleRatio;
        if( img_set_ ) {
            scaleRatio = 500.0 / qimage_.size().height();
            painter.drawImage(QPoint(0,0), qimage_.scaledToHeight(500));
        }

        // Draw contours
        if( contours_set_ )
            for(std::vector<cv::Point>& contour : contours_)
                for(unsigned i = 0, j = 1; i < contour.size(); i++, j++, j %= contour.size()) {
                    QPoint a(contour[i].x * scaleRatio, contour[i].y * scaleRatio);
                    QPoint b(contour[j].x * scaleRatio, contour[j].y * scaleRatio);
                    painter.drawLine(a, b);
                }

        painter.end();
    }

    QString& errbuf() {
        errbuf_.clear();
        return errbuf_;
    }

    bool img_set_;
    cv::Mat img_;
    QImage qimage_;
    QPen qpen_;

    QString errbuf_;

    bool plugin_set_;
    QString pluginShapeName_;
    QObject* plugin_;
    QPluginLoader loader_;

    bool contours_set_;
    std::vector<std::vector<cv::Point>> contours_;
};

#endif // CVIMAGEWIDGET_H
