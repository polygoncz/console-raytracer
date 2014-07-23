TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    film.cpp \
    progressbar.cpp \
    primitive.cpp \
    light.cpp \
    geometry.cpp \
    camera.cpp \
    material.cpp

HEADERS += \
    geometry.h \
    core.h \
    intersection.h \
    film.h \
    color.h \
    progressbar.h \
    light.h \
    material.h \
    primitive.h \
    camera.h

