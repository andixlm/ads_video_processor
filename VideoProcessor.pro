QT += core gui widgets

TARGET = VideoProcessor
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp \
    clickablelabel.cpp \
    boxes.cpp \
    buttons.cpp \
    imagetree.cpp \
    imagewindow.cpp \
    menus.cpp \
    modes.cpp \
    player.cpp \
    polygon.cpp \
    rgb.cpp \
    spins.cpp \
    tools.cpp

HEADERS += mainwindow.h \
    clickablelabel.h \
    exception.h \
    imagetree.h \
    imagewindow.h \
    player.h \
    polygon.h \
    rgb.h \
    tools.h

FORMS += mainwindow.ui \
    imagewindow.ui

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
