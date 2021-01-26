#include "mainwindow.h"

#include <vector>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    cv::VideoCapture cam(0);
//    cv::namedWindow("cam");
//    cv::Mat temp;
//    cam >> temp;
//    cv::imshow("cam",temp);
//    cv::waitKey(0);
//    cam.release();
    return a.exec();
}
