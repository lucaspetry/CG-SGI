greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Configurações gerais
TEMPLATE = app
LANGUAGE = C++
QT += core gui

# Arquitetura de destino (ainda necessário configuração)
CONFIG += 64bit
CONFIG(32bit) {
    TARGET = SGIx86.app
    QMAKE_CXXFLAGS += -m32
    LIBS += -L<x86 libraries path>
} else {
    TARGET = SGI.app
}

# C++ flags
QMAKE_CXX = g++
QMAKE_CXXFLAGS_WARN_ON = -Wall
QMAKE_CXXFLAGS_RELEASE = -std=c++11
QMAKE_CXXFLAGS_DEBUG = -std=c++11 -g

# Inclusões e bibliotecas
INCLUDEPATH += include
LIBS +=

# Diretórios de destino
OBJECTS_DIR = temp
MOC_DIR = temp	
UI_DIR = include/gui/forms/ui

# Arquivos de cabeçalho
HEADERS  += include/gui/forms/*.h \

# Arquivos fonte
SOURCES += src/gui/*.cpp \
src/gui/clipping/*.cpp \
src/gui/forms/*.cpp \
src/controle/*.cpp \
src/geometria/*.cpp \
src/persistencia/*.cpp \

# Arquivos de formulário
FORMS    += src/gui/forms/ui/*.ui \
