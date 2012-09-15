#-------------------------------------------------
#
# Project created by QtCreator 2012-09-14T15:45:06
#
#-------------------------------------------------

QT       += core gui

TARGET      = stereo-vision-client
TEMPLATE    = app


SOURCES += main.cpp\
           gui.cpp \
           Engine/dataretriever.cpp \
    Widgets/processstep.cpp

HEADERS  += gui.h \
            Engine/dataretriever.h \
    Widgets/processstep.h

FORMS    += gui.ui \
    Widgets/processstep.ui
