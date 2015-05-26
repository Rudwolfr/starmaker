#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T15:49:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StarMaker
TEMPLATE = app


SOURCES += main.cpp\
        starmaker.cpp \
    planetmaker.cpp

HEADERS  += starmaker.h \
    planetmaker.h

FORMS    += starmaker.ui \
    PlanetMaker.ui

win32 {
QMAKE_LFLAGS += -static-libgcc -static-libstdc++
}

TRANSLATIONS = starmaker_en.ts

RESOURCES += \
    starmaker.qrc

OTHER_FILES +=
