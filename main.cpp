#include "mainwindow.h"

#include <vector>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QRegExp>
#include <QString>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QRegExp temp(QString::fromLocal8Bit("\u662f"));
    QString target = QString::fromLocal8Bit("是");
    if(temp.exactMatch(target))
    {
        QMessageBox::about(nullptr,"ok","success");
    }
//    cv::VideoCapture cam(0);
//    cv::namedWindow("cam");
//    cv::Mat temp;
//    cam >> temp;
//    cv::imshow("cam",temp);
//    cv::waitKey(0);
//    cam.release();
    return a.exec();
}
