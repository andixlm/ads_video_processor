QT += core gui widgets

TARGET = VideoProcessor
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp \
    buttons.cpp \
    imagetree.cpp \
    imageview.cpp \
    menus.cpp \
    modebox.cpp \
    player.cpp \
    polygon.cpp \
    rgb.cpp

HEADERS += mainwindow.h \
    exception.h \
    imagetree.h \
    imageview.h \
    player.h \
    polygon.h \
    rgb.h

FORMS += mainwindow.ui \
    imageview.ui

# OpenCV support
INCLUDEPATH += $$PWD\\opencv\\include
LIBS += -L$$PWD\\opencv\\bin \
    -llibopencv_calib3d2413d \
    -llibopencv_contrib2413d \
    -llibopencv_core2413d \
    -llibopencv_features2d2413d \
    -llibopencv_flann2413d \
    -llibopencv_gpu2413d \
    -llibopencv_highgui2413d \
    -llibopencv_imgproc2413d \
    -llibopencv_legacy2413d \
    -llibopencv_ml2413d \
    -llibopencv_nonfree2413d \
    -llibopencv_objdetect2413d \
    -llibopencv_ocl2413d \
    -llibopencv_photo2413d \
    -llibopencv_stitching2413d \
    -llibopencv_superres2413d \
    -llibopencv_video2413d \
    -llibopencv_videostab2413d \
    -lopencv_ffmpeg2413
