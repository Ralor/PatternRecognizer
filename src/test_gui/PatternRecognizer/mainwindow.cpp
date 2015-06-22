#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cvimagewidget.h>

#include <QFileDialog>
#include <QFileInfo>
#include <QColorDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open image"),
                                                    "/",
                                                    tr("Images (*.png *.bmp *.jpg)"));

    CVImageWidget* canvas = this->centralWidget()->findChild<CVImageWidget*>("formWidget");
    if( !canvas->showImage(path) && path.size() ) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", canvas->errorString());
        messageBox.setFixedSize(500,200);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open plugin"),
                                                    "/",
                                                    tr("Shared libs (*.dll)"));
    CVImageWidget* canvas = this->centralWidget()->findChild<CVImageWidget*>("formWidget");
    if( !canvas->loadPlugin(path) && path.size() ) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", canvas->errorString());
        messageBox.setFixedSize(500,200);
    } else {
        QLabel* label;
        label = this->centralWidget()->findChild<QLabel*>("label_4");
        label->setText(QFileInfo(path).fileName());
        label = this->centralWidget()->findChild<QLabel*>("label");
        label->setText("Plugin shape: " + canvas->getPluginShape());
        label = this->centralWidget()->findChild<QLabel*>("label_2");
        label->setText("Plugin description: " + canvas->getPluginDescription() +
                       "\n(tested for " + canvas->getPluginSuccessPercentage() + "\%)");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    CVImageWidget* canvas = this->centralWidget()->findChild<CVImageWidget*>("formWidget");
    if( !canvas->paintContours() ) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", canvas->errorString());
        messageBox.setFixedSize(500,200);
    } else {
        QLabel* label;
        label = this->centralWidget()->findChild<QLabel*>("label_3");
        label->setText("Shapes found: " + QString::number(canvas->shapesCount()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QPushButton* btn = this->centralWidget()->findChild<QPushButton*>("pushButton_2");
    QColor color = QColorDialog::getColor();
    CVImageWidget* canvas = this->centralWidget()->findChild<CVImageWidget*>("formWidget");
    canvas->setPenColor(color);
    int r, g, b;
    color.getRgb(&r, &g, &b);
    QString stylesheet;
    stylesheet.sprintf("background-color: rgb(%d, %d, %d); ", r, g, b);
    btn->setStyleSheet(stylesheet);
    repaint();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    CVImageWidget* canvas = this->centralWidget()->findChild<CVImageWidget*>("formWidget");
    canvas->setPenWidth(value);
    canvas->repaint();
}
