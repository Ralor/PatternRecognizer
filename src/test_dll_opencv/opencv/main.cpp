#include <cvimagewidget.h>

#include <QApplication>
#include <QMainWindow>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    // Create the image widget
    CVImageWidget* imageWidget = new CVImageWidget();
    window.setCentralWidget(imageWidget);

    // Load an image
    cv::Mat image = cv::imread("C:/dev/PatternRecognizer/tests/circle_4_1_6.jpg", true);
    imageWidget->showImage(image);

    window.show();

    return a.exec();
}
