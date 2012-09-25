#-------------------------------------------------
#
# Project created by QtCreator 2012-09-14T15:45:06
#
#-------------------------------------------------

QT       += core gui

TARGET      = stereo-vision-client
TEMPLATE    = app


SOURCES +=  main.cpp\
            gui.cpp \
            Engine/dataretriever.cpp \
            Widgets/processstepWidget.cpp \
            Engine/engine.cpp \
            DataTypes/abstractparameter.cpp

HEADERS  += gui.h \
            Engine/dataretriever.h \
            Widgets/processstepWidget.h \
            Engine/engine.h \
            DataTypes/abstractparameter.h

FORMS    += gui.ui \
            Widgets/processstepWidget.ui

OTHER_FILES +=
