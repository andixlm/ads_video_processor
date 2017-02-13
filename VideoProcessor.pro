QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoProcessor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui

# OpenCV support
LIBS += $$PWD\opencv\bin\libopencv*.dll \
    $$PWD\opencv\bin\opencv_ffmpeg2413.dll
INCLUDEPATH += $$PWD\opencv\include
