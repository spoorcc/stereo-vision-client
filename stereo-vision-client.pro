#-------------------------------------------------
#
# Project created by QtCreator 2012-09-14T15:45:06
#
#-------------------------------------------------

QT       += core gui network

TARGET      = stereo-vision-client
TEMPLATE    = app


SOURCES +=  main.cpp\
            gui.cpp \
            Widgets/processstepWidget.cpp \
            Engine/engine.cpp \
            DataTypes/abstractparameter.cpp \
            DataTypes/numericparameter.cpp \
            DataTypes/booleanparameter.cpp \
            Widgets/parameterwidget.cpp \
            DataTypes/processstep.cpp \
    Engine/dataTransciever.cpp

HEADERS  += gui.h \
            Widgets/processstepWidget.h \
            Engine/engine.h \
            DataTypes/abstractparameter.h \
            DataTypes/numericparameter.h \
            DataTypes/booleanparameter.h \
            Widgets/parameterwidget.h \
            DataTypes/processstep.h \
    Engine/dataTransciever.h

FORMS    += gui.ui \
            Widgets/processstepWidget.ui \
            Widgets/parameterwidget.ui

OTHER_FILES +=
