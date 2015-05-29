#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T18:05:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Warcaby
TEMPLATE = app


SOURCES += main.cpp\
    game.cpp \
    pawn.cpp \
    QtVisualisationMainWindow.cpp \
    QtVisualisationBoard.cpp

HEADERS  += \
    game.h \
    pawn.h \
    QtVisualisationMainWindow.h \
    QtVisualisationBoard.h

FORMS    += \
    QtVisualisationMainWindow.ui
