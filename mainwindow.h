#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <opencv2/opencv.hpp>
#include <QMessageBox>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QBrush>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    static void show_thread(void *m);
    ~MainWindow();
    bool cam_open;
private slots:
    void open_cam();
    void get_pic();
    void close_cam();
    void show_pic();
    void deal_pic();


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
//    cv::VideoCapture *cam;
//    cv::Mat pic;
    QTimer *timer;

};
#endif // MAINWINDOW_H
