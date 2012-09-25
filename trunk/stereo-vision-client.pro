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
            DataTypes/abstractparameter.cpp \
            DataTypes/numericparameter.cpp \
    DataTypes/booleanparameter.cpp \
    Widgets/parameterwidget.cpp

HEADERS  += gui.h \
            Engine/dataretriever.h \
            Widgets/processstepWidget.h \
            Engine/engine.h \
            DataTypes/abstractparameter.h \
            DataTypes/numericparameter.h \
    DataTypes/booleanparameter.h \
    Widgets/parameterwidget.h

FORMS    += gui.ui \
            Widgets/processstepWidget.ui \
    Widgets/parameterwidget.ui

OTHER_FILES +=
