QT       += core gui

TARGET = fruitclick-qt
TEMPLATE = app
DESTDIR = ../fruitclick-qt

INCLUDEPATH += ../fruitclick
LIBS += -L../fruitclick -lfruitclick

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h
