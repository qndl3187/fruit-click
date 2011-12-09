QT -= core gui

TARGET = fruitclick
TEMPLATE = lib
DESTDIR = ../fruitclick

DEFINES += FRUITCLICK_LIBRARY
LIBS += -L../fruitclick -lbox2d
INCLUDEPATH += .

SOURCES += platform.cpp \
    application.cpp \
    apple.cpp \
    grass.cpp \
    b2dobject.cpp \
    bound.cpp \
    utils.cpp
HEADERS += platform.h\
    export.h \
    application.h \
    apple.h \
    grass.h \
    b2dobject.h \
    bound.h \
    utils.h
















