# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

QT += core gui sql widgets
TEMPLATE = app
TARGET = stu_manager_sys
DESTDIR = ./x64/Debug
CONFIG += debug
LIBS += -L"../../../mysql-8.0.18-winx64/lib" \
    -llibmysql
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += debug
UI_DIR += .
RCC_DIR += .
HEADERS += ./mainwindow.h
SOURCES += ./main.cpp \
    ./mainwindow.cpp
FORMS += ./mainwindow.ui
RESOURCES += mainwindow.qrc