#-------------------------------------------------
#
# Project created by QtCreator 2019-02-18T13:03:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Exercise2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    renderingwidget.cpp \
    transformwidget.cpp \
    inspectorwidget.cpp \
    myopenglwidget.cpp \
    customwidget.cpp \
    primitive.cpp \
    entitylabelwidget.cpp \
    entity.cpp \
    entitylabel.cpp \
    hyerarchylistwidget.cpp

HEADERS += \
        mainwindow.h \
    renderingwidget.h \
    transformwidget.h \
    inspectorwidget.h \
    myopenglwidget.h \
    customwidget.h \
    entity.h \
    primitive.h \
    entitylabelwidget.h \
    entitylabel.h \
    hyerarchylistwidget.h

FORMS += \
        mainwindow.ui \
    rendering.ui \
    transformwidget.ui \
    hyerarchywidget.ui \
    entitylabelwidget.ui \
    hyerarchylistwidget.ui

RESOURCES += \
    icons.qrc \
    icons.qrc

# Adds OpenGL library
QT      += opengl

# Opens a console during execution to show debug logs
CONFIG += console
