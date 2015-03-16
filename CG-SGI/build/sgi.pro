greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
LANGUAGE = C++
QT += core gui

QMAKE_CXX = g++
QMAKE_CXXFLAGS_WARN_ON = -Wall
QMAKE_CXXFLAGS_RELEASE = -O2 -std=c++11
QMAKE_CXXFLAGS_DEBUG = -std=c++11 -g

INCLUDEPATH += include
LIBS +=

OBJECTS_DIR = temp
MOC_DIR = temp	
UI_DIR = include/gui/forms/ui

TARGET = SGI.app

HEADERS  += include/gui/forms/*.h \

SOURCES += src/gui/forms/*.cpp \
src/controle/*.cpp \
src/geometria/*.cpp \

FORMS    += src/gui/forms/ui/*.ui \