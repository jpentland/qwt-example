# Qt project file - qmake uses his to generate a Makefile

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Volumeter

LIBS += -lqwt -lm -lbcm2835 -lrt

HEADERS += window.h adc.h gz_clk.h ledout.h

SOURCES += main.cpp window.cpp adc.c gz_clk.c ledout.c

