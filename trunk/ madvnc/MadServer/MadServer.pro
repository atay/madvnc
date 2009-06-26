TEMPLATE = app
CONFIG   += console
CONFIG   -= app_bundle
TARGET = MadServer
QT += core \
    gui \
    network
HEADERS += MadPix.h \
    MadServer.h
SOURCES += MadPix.cpp \
    MadServer.cpp \
    main.cpp
FORMS += 
RESOURCES += 
