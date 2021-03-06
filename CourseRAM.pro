#-------------------------------------------------
#
# Project created by QtCreator 2020-04-19T15:17:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Course
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

CONFIG += c++11

SOURCES += \
    RAM.cpp \
        main.cpp \
        mainwindow.cpp \
    editnotewindow.cpp \
    table.cpp \
    addnotewindow.cpp

HEADERS += \
    RAM.h \
        mainwindow.h \
    editnotewindow.h \
    table.h \
    addnotewindow.h

FORMS += \
        mainwindow.ui \
    editnotewindow.ui \
    addnotewindow.ui

TRANSLATIONS += Course_ru.ts \
                Course_eng.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Course_eng.ts \
    Course_ru.ts

RESOURCES += \
    resource.qrc \
    resource.qrc
