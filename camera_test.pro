QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#INCLUDEPATH += "E:\Opencv\4.2.0\install\include"
#INCLUDEPATH += E:\Opencv\4.2.0\install\include\opencv2
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\bin -lopencv_calib3d420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\bin -lopencv_core420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\lib -lopencv_dnn420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\lib -lopencv_features2d420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\lib -lopencv_flann420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\lib -lopencv_gapi420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\bin -lopencv_highgui420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\bin -lopencv_imgcodecs420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\bin -lopencv_imgproc420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\lib -lopencv_ml420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\lib -lopencv_objdetect420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\lib -lopencv_photo420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\lib -lopencv_stitching420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\lib -lopencv_video420
#LIBS+= -LE:\Opencv\4.2.0\install\x64\vc16\lib -lopencv_videoio420

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

#INCLUDEPATH += "F:\opencv-4.2.0\build\qt\install\include"
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_calib3d420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_core420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_dnn420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_features2d420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_flann420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_gapi420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_highgui420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_imgcodecs420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_imgproc420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_ml420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_objdetect420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_photo420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_stitching420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_video420
#LIBS+= -LF:\opencv-4.2.0\build\qt\install\x64\mingw\lib -lopencv_videoio420


INCLUDEPATH+=E:\Opencv\3.4.10\install\include     #包含路径
INCLUDEPATH+=E:\Opencv\3.4.10\install\include\opencv
INCLUDEPATH+=E:\Opencv\3.4.10\install\include\opencv2
INCLUDEPATH+=E:\code\ZBar\include
INCLUDEPATH+=E:\code\ZBar\include\zbar

CONFIG(debug, debug|release): {
LIBS += E:\Opencv\3.4.10\install\x64\vc16\lib\*.lib   #包含的库
}
CONFIG(release, debug|release): {
LIBS += E:\Opencv\3.4.10\lib\Release\opencv_world3410.lib
LIBS += E:\code\ZBar\lib\libzbar64-0.lib

}




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
