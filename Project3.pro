TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    celestial_body.cpp \
    planetary_system.cpp \
    read_file.cpp

LIBS += -larmadillo -lblas -llapack -lunittest++ -lrt

HEADERS += \
    celestial_body.h \
    planetary_system.h \
    read_file.h
