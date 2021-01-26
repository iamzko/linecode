#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QGraphicsScene>
#include <QFileDialog>
#include <thread>
#include <QtDebug>
#include <QThread>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/types_c.h"
#include <opencv2/core/cvdef.h>

#include <zbar.h>


//#define IMSHOW

const QString temp_pic_path = "./temp_pic";

QImage cvMat2QImage(const cv::Mat& cvImg)
{
    QImage qImg;
    if (cvImg.channels() == 3)                             //三通道彩色图像
    {
        //CV_BGR2RGB
        cv::cvtColor(cvImg, cvImg, CV_RGB2BGR);
        qImg = QImage((const unsigned char*)(cvImg.data), cvImg.cols, cvImg.rows, cvImg.cols*cvImg.channels(), QImage::Format_RGB888);
    }
    else if (cvImg.channels() == 1)                    //单通道（灰度图）
    {
        qImg = QImage((const unsigned char*)(cvImg.data), cvImg.cols, cvImg.rows, cvImg.cols*cvImg.channels(), QImage::Format_Indexed8);

        QVector<QRgb> colorTable;
        for (int k = 0; k<256; ++k)
        {
            colorTable.push_back(qRgb(k, k, k));
        }
        qImg.setColorTable(colorTable);//把qImg的颜色按像素点的颜色给设置
    }
    else
    {
        qImg = QImage((const unsigned char*)(cvImg.data), cvImg.cols, cvImg.rows, cvImg.cols*cvImg.channels(), QImage::Format_RGB888);
    }
    return qImg;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,cam_open(false), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    timer= new QTimer(this);
//    QObject::connect(timer,&QTimer::timeout,this,&MainWindow::get_pic);
    QDir temp_dir;
    if(!temp_dir.exists(temp_pic_path))
    {
        temp_dir.mkdir(temp_pic_path);
        qDebug("mkdir !");
    }
}

MainWindow::~MainWindow()
{
    close_cam();
    delete ui;
}

void MainWindow::open_cam()
{
//    if(cam == nullptr)
//    {
//        cam_open = true;
//        cam = new cv::VideoCapture(0);
//        //    std::thread t(show_thread,this);
//        //    t.detach();
//        timer->start(33);

//    }
//    else
//    {
//        QMessageBox::critical(this,"error","cam have opened!!!");
//    }

}
void MainWindow::show_thread(void *m)
{
    while(reinterpret_cast<MainWindow *>(m)->cam_open)
    {

        reinterpret_cast<MainWindow *>(m)->get_pic();
        QThread::msleep(10);
        printf("one\n");

    }
}
void MainWindow::get_pic()
{
//    *cam >> pic;
//    cv::namedWindow("cam");
//    cv::imshow("cam",pic);
//    cv::waitKey(1);
//    cvtColor(pic, pic, cv::COLOR_BGR2RGB);//

//    QImage src = QImage((uchar*)(pic.data),pic.cols,pic.rows,QImage::Format_RGB888);
//    ui->label->setPixmap(QPixmap::fromImage(src));
//    ui->label->show();
    //    QGraphicsScene *s = new QGraphicsScene;
    //    s->addPixmap(QPixmap::fromImage(src));
    //    ui->graphicsView->setScene(s);
    //    ui->graphicsView->show();
    //    printf("ok\n");
    //    qDebug() << "ok";
    //    if(s)
    //    delete s;


}


void MainWindow::close_cam()
{
//    if(cam)
//    {
//        cam_open = false;
//        cam->release();
//    }
}
void MainWindow::show_pic()
{
    std::vector<int> color{32,96,160,224};
    QPixmap pix = QPixmap(ui->label->width(),ui->label->height());
    pix.fill(Qt::white);
    QPainter p;
    p.begin(&pix);
    int sx = 10;
    int sy = 10;
    int len = 20;
    int mid = 5;
    int col = 0;
    int row = 0;

    for(auto r:color)
    {
        for(auto g:color)
        {
            for(auto b:color)
            {

                p.setBrush(QBrush(QColor(r,g,b)) );
                if(sx+(col+1)*(len+mid) < ui->label->width()-sx)
                {
                    p.drawRect(sx+col*(len+mid),sy+row *(len+mid),len,len);
                    qDebug("(%d,%d,%d)\t",r,g,b);
                    col += 1;
                }
                else
                {
                    qDebug("\n");
                    col = 0;
                    row += 1;
                }

            }
        }
    }
    p.end();
    //    update();
    ui->label->setPixmap(pix);
    ui->label->show();


}

void MainWindow::on_pushButton_clicked()
{
    //    show_pic();
    deal_pic();
}
void MainWindow::deal_pic()
{
    ui->label_2->clear();
    QFileDialog *fileDialog = new QFileDialog();
    //定义文件对话框标题
    fileDialog->setWindowTitle(QFileDialog::tr("打开文件"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(QFileDialog::tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    //    fileDialog->setNameFilter(tr("text(*.txt)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //获取选中文件路径
    QStringList fileNames;
    if (fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    if(fileNames.empty())
    {
        return;
    }
    qDebug("%s",fileNames.at(0).toLocal8Bit().data());
    cv::Mat image,imageGray,imageGuussian;
    cv::Mat imageSobelX,imageSobelY,imageSobelOut;

    auto cv_str = cv::String(fileNames.first().toUtf8().data());
    qDebug("%s",cv_str.c_str());
    image=cv::imread(cv_str);
#ifdef IMSHOW
    imshow(QString::fromUtf8("0.原图像").toLocal8Bit().data(),image);
#endif

    //1. 原图像大小调整，提高运算效率
//    cv::resize(image,image,cv::Size(500,300));
#ifdef IMSHOW

    imshow(QString::fromUtf8("1.原图像").toLocal8Bit().data(),image);
#endif
    //2. 转化为灰度图
    cvtColor(image,imageGray,CV_RGB2GRAY);
#ifdef IMSHOW

    imshow(QString::fromUtf8("2.灰度图").toLocal8Bit().data(),imageGray);
#endif
    //3. 高斯平滑滤波
    GaussianBlur(imageGray,imageGuussian,cv::Size(3,3),0);
#ifdef IMSHOW

    imshow(QString::fromUtf8("3.高斯平衡滤波").toLocal8Bit().data(),imageGuussian);
#endif
    //4.求得水平和垂直方向灰度图像的梯度差,使用Sobel算子
    cv::Mat imageX16S,imageY16S;
    Sobel(imageGuussian,imageX16S,CV_16S,1,0,3,1,0,4);
    Sobel(imageGuussian,imageY16S,CV_16S,0,1,3,1,0,4);
    convertScaleAbs(imageX16S,imageSobelX,1,0);
    convertScaleAbs(imageY16S,imageSobelY,1,0);
    imageSobelOut=imageSobelX-imageSobelY;
#ifdef IMSHOW

    imshow(QString::fromUtf8("4.X方向梯度").toLocal8Bit().data(),imageSobelX);
    imshow(QString::fromUtf8("4.Y方向梯度").toLocal8Bit().data(),imageSobelY);
    imshow(QString::fromUtf8("4.XY方向梯度差").toLocal8Bit().data(),imageSobelOut);
#endif
    //5.均值滤波，消除高频噪声
    blur(imageSobelOut,imageSobelOut,cv::Size(3,3));
#ifdef IMSHOW

    imshow(QString::fromUtf8("5.均值滤波").toLocal8Bit().data(),imageSobelOut);
    #endif

    //6.二值化
    cv::Mat imageSobleOutThreshold;
    threshold(imageSobelOut,imageSobleOutThreshold,100,255,CV_THRESH_BINARY);
#ifdef IMSHOW

    imshow(QString::fromUtf8("6.二值化").toLocal8Bit().data(),imageSobleOutThreshold);
    #endif





    //7.闭运算，填充条形码间隙
    cv::Mat  element=getStructuringElement(0,cv::Size(7,7));
    morphologyEx(imageSobleOutThreshold,imageSobleOutThreshold,cv::MORPH_CLOSE,element);
#ifdef IMSHOW

    imshow(QString::fromUtf8("7.闭运算").toLocal8Bit().data(),imageSobleOutThreshold);
#endif
    //8. 腐蚀，去除孤立的点
    erode(imageSobleOutThreshold,imageSobleOutThreshold,element);
#ifdef IMSHOW

    imshow(QString::fromUtf8("8.腐蚀").toLocal8Bit().data(),imageSobleOutThreshold);
#endif

    //9. 膨胀，填充条形码间空隙，根据核的大小，有可能需要2~3次膨胀操作
    dilate(imageSobleOutThreshold,imageSobleOutThreshold,element);
    dilate(imageSobleOutThreshold,imageSobleOutThreshold,element);
    dilate(imageSobleOutThreshold,imageSobleOutThreshold,element);
    dilate(imageSobleOutThreshold,imageSobleOutThreshold,element);
#ifdef IMSHOW

    imshow(QString::fromUtf8("9.膨胀").toLocal8Bit().data(),imageSobleOutThreshold);
#endif


    std::vector<std::vector<cv::Point>> contours3;
    std::vector<cv::Vec4i> hiera;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Rect> boundRect(contours.size());
    //注意第5个参数为CV_RETR_EXTERNAL，只检索外框
    findContours(imageSobleOutThreshold, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //找轮廓
    std::cout << contours.size() << std::endl;
    for (auto i = 0; i < contours.size(); ++i)
    {
        //需要获取的坐标
        cv::Point2f rectpoint[4];
        //取得最小外接矩形
        auto rect =cv::minAreaRect(cv::Mat(contours[i]));
        //获取4个顶点坐标
        rect.points(rectpoint);
        qDebug("point1:%f,%f,point2:%f,%f,point3:%f,%f,point4:%f,%f,continue!",rectpoint[0].x,rectpoint[0].y,rectpoint[1].x,rectpoint[1].y,rectpoint[2].x,rectpoint[2].y,rectpoint[3].x,rectpoint[3].y);
        cv::Mat test_image = imageSobleOutThreshold.clone();
        for (int i = 0; i < 4; i++)
            line(test_image, rectpoint[i], rectpoint[(i+1)%4], cv::Scalar(255,0,255), 2);
#ifdef IMSHOW

        imshow("9.1test_image",test_image);
#endif
        //与水平线的角度
        float angle = rect.angle;

        int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
        int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
        rectangle(imageSobleOutThreshold, rectpoint[0], rectpoint[3], cv::Scalar(255), 2);
        //面积太小的直接pass
        if (line1 * line2 < 600)
        {
            qDebug("line1:%d,line2:%d,continue!",line1,line2);
            continue;
        }

        //为了让正方形横着放，所以旋转角度是不一样的。竖放的，给他加90度，翻过来
        if (line1 > line2)
        {
            angle = 90 + angle;
        }

        //新建一个感兴趣的区域图，大小跟原图一样大
        cv::Mat RoiSrcImg(image.rows, image.cols, CV_8UC3); //注意这里必须选CV_8UC3
        RoiSrcImg.setTo(255); //颜色都设置为黑色
        //imshow("新建的ROI", RoiSrcImg);
        //对得到的轮廓填充一下
        drawContours(imageSobleOutThreshold, contours, -1, cv::Scalar(255),-1);

        //抠图到RoiSrcImg
        image.copyTo(RoiSrcImg, imageSobleOutThreshold);


        //再显示一下看看，除了感兴趣的区域，其他部分都是黑色的了
//        cv::namedWindow("RoiSrcImg", 1);
#ifdef IMSHOW

        imshow("9.2RoiSrcImg", RoiSrcImg);
#endif
        //获取有效区域
        auto target_rect =boundingRect((cv::Mat)contours[i]);
        cv::Mat img_part = RoiSrcImg(target_rect);
#ifdef IMSHOW

        imshow("9.2.1_the_img_part",img_part);
#endif
        QString temp_pic_part_name;
        temp_pic_part_name += temp_pic_path +"/";
        temp_pic_part_name += QString::number(i) + "_part.jpg";
        cv::imwrite(temp_pic_part_name.toLocal8Bit().data(),img_part);
        cv::resize(img_part,img_part,cv::Size(img_part.cols*2,img_part.rows*2));

        //创建一个旋转后的图像
        cv::Mat RatationedImg(img_part.rows, img_part.cols, CV_8UC1);
        RatationedImg.setTo(255);
        //对RoiSrcImg进行旋转
        cv::Point2f center = rect.center;  //中心点
        qDebug() << "the center x:" << center.x << ";y:" << center.y;
        //计算旋转加缩放的变换矩阵
        cv::Mat M2 = getRotationMatrix2D(center, angle, 1);
        //仿射变换
        warpAffine(img_part, RatationedImg, M2, img_part.size(),1, 0, cv::Scalar(255,255,255));
#ifdef IMSHOW

        cv::imshow(QString::fromUtf8("9.3旋转之后").toLocal8Bit().data(), RatationedImg);
#endif
        //将矫正后的图片保存下来
        QString temp_pic_name;
        temp_pic_name += temp_pic_path + "/";
        temp_pic_name += QString::number(i) +".jpg";
        qDebug() << temp_pic_name;
        cv::imwrite(temp_pic_name.toLocal8Bit().data(), RatationedImg);

        qDebug("check begin!");

        //zbar开始
        zbar::ImageScanner scan;
        scan.set_config(zbar::ZBAR_NONE,zbar::ZBAR_CFG_ENABLE,1);
        //构建zbar图像
        cv::Mat img_gray;
        cv::cvtColor(RatationedImg,img_gray,CV_RGB2GRAY);
#ifdef IMSHOW

        cv::imshow("9.4ratation_gray",img_gray);
#endif
        qDebug() << "cols:" << img_gray.cols << ";rows:" << img_gray.rows;
        uchar* raw_data = (uchar*)img_gray.data;
        zbar::Image img_zbar(img_gray.cols,img_gray.rows,"Y800",raw_data,img_gray.cols * img_gray.rows);
        //扫描
        qDebug("scan begin!");
        scan.scan(img_zbar);
        zbar::Image::SymbolIterator symbol = img_zbar.symbol_begin();
        if(img_zbar.symbol_begin() == img_zbar.symbol_end())
        {
            qDebug("check failed!");
//            return;
        }
        for(auto symbol = img_zbar.symbol_begin();symbol != img_zbar.symbol_end(); ++symbol)
        {
            qDebug() << "type:" << symbol->get_type_name().c_str();
            qDebug() << "code:" << symbol->get_data().c_str();
        }
        img_zbar.set_data(nullptr,0);
        qDebug() << i << "*******************************************";


        rectangle(image,target_rect,cv::Scalar(255),2);
#ifdef IMSHOW

        cv::imshow(QString::fromUtf8("10.找出二维码矩形区域").toLocal8Bit().data(),image);
#endif

        QImage img_to_show = cvMat2QImage(image);
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap::fromImage(img_to_show));
        if(img_zbar.symbol_begin() != img_zbar.symbol_end())
        {
            QString text_to_show = ui->label_2->text();
            text_to_show += "type:";
            text_to_show += symbol->get_type_name().c_str();
            text_to_show += "\r\ncode:";
            text_to_show += symbol->get_data().c_str();
            text_to_show += "\r\n";
            ui->label_2->setText(text_to_show);

        }


#if 0
    //10.通过findContours找到条形码区域的矩形边界
    findContours(imageSobleOutThreshold,contours,hiera,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    for(int i=0;i<contours3.size();i++)
    {
        cv::Rect rect=boundingRect((cv::Mat)contours3[i]);
        rectangle(image,rect,cv::Scalar(255),2);
    }
    cv::imshow(QString::fromUtf8("10.找出二维码矩形区域").toLocal8Bit().data(),image);
#endif
    }

#if 0
    //对ROI区域进行抠图

    //对旋转后的图片进行轮廓提取
    std::vector<std::vector<cv::Point> > contours2;
    cv::Mat raw = cv::imread("r.jpg");
    cv::Mat SecondFindImg;
    //SecondFindImg.setTo(0);
    cvtColor(raw, SecondFindImg, cv::COLOR_BGR2GRAY);  //灰度化
    threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
    findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //cout << "sec contour:" << contours2.size() << endl;

    for (int j = 0; j < contours2.size(); j++)
    {
        //这时候其实就是一个长方形了，所以获取rect
        cv::Rect rect = boundingRect(cv::Mat(contours2[j]));
        //面积太小的轮廓直接pass,通过设置过滤面积大小，可以保证只拿到外框
        if (rect.area() < 600)
        {
            continue;
        }
        cv::Mat dstImg = raw(rect);
        imshow("dst", dstImg);
    }
#endif



}
