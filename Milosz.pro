#-------------------------------------------------
#
# Project created by QtCreator 2014-01-03T19:40:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Milosz
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        miloszqt.cpp \
    gra.cpp \
    milosz.cpp \
    pole.cpp \
    prymitywne.cpp \
    rozwiniete.cpp \
    stworzenie.cpp \
    textplansza.cpp \
    randengine.cpp

HEADERS  += miloszqt.h \
    gra.h \
    milosz.h \
    pole.h \
    prymitywne.h \
    rozwiniete.h \
    stworzenia.h \
    stworzenie.h \
    textplansza.h \
    randengine.h

FORMS    +=

OTHER_FILES += \
    map1.txt \
    map2.txt \
    map9.txt \
    README.md
