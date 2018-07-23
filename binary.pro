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
    ofEx.h \
    floatP.h \
    ufEx.h \
    integer.h \
    float16.h \
    sigMag.h \
    zeroex.h \
    opEx.h
