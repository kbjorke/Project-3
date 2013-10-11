TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    RungeKutta4.cpp \
    celestial_body.cpp \
    planetary_system.cpp

LIBS += -larmadillo -lblas -llapack -lunittest++ -lrt

HEADERS += \
    celestial_body.h \
    planetary_system.h
