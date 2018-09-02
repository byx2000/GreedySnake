#-------------------------------------------------
#
# Project created by QtCreator 2018-07-09T21:28:03
#
#-------------------------------------------------

QT       += core gui
RC_ICONS = images/snake.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GreedySnake
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
        waittingpage.cpp \
    aboutpage.cpp \
    global.cpp \
    hintpage.cpp \
    pausingpage.cpp \
    gamepage.cpp \
    game/GreedySnakeGame.cpp \
    game/ObserverMode.cpp \
    game/Snake.cpp \
    game/SnakeNode.cpp \
    toastwindow.cpp \
    bufferwindow.cpp

HEADERS += \
        waittingpage.h \
    aboutpage.h \
    global.h \
    hintpage.h \
    pausingpage.h \
    gamepage.h \
    game/GreedySnakeGame.h \
    game/ObserverMode.h \
    game/Snake.h \
    game/SnakeNode.h \
    toastwindow.h \
    bufferwindow.h

FORMS += \
        waittingpage.ui \
    aboutpage.ui \
    hintpage.ui \
    pausingpage.ui \
    gamepage.ui \
    toastwindow.ui \
    bufferwindow.ui

RESOURCES += \
    images.qrc
