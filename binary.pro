TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    twosComp.cpp \
    floatP.cpp \
    integer.cpp \
    binary.cpp \
    float16.cpp \
    sigMag.cpp

HEADERS += \
    binary.h \
    twosComp.h \
    floatP.h \
    integer.h \
    float16.h \
    sigMag.h \
    opEx.h
