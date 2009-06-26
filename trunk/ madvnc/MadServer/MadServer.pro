TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
TARGET = MadServer
QT += core \
    gui \
    network
HEADERS += ScreenShooter.h \
    MadPix.h \
    MadServer.h
SOURCES += ScreenShooter.cpp \
    MadPix.cpp \
    MadServer.cpp \
    main.cpp
FORMS += 
RESOURCES += 
