#-------------------------------------------------
#
# Project created by QtCreator 2020-01-31T08:45:16
#
#-------------------------------------------------

QT       += core gui

INCLUDEPATH += $$PWD/opencv-3.4.1-output/include
               $$PWD/opencv-3.4.1-output/include/opencv
               $$PWD/opencv-3.4.1-output/include/opencv2

LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_calib3d341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_core341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_dnn341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_features2d341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_flann341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_highgui341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_imgcodecs341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_imgproc341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_ml341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_objdetect341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_photo341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_shape341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_stitching341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_superres341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_video341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_videoio341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_videostab341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/opencv_ffmpeg341.dll
LIBS += $$PWD/opencv-3.4.1-output/lib/libopencv_face341.dll

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceExtraction
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
