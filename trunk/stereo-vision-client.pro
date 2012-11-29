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
            Widgets/parameterwidget.cpp \
            DataTypes/processstep.cpp \
            Engine/dataTransciever.cpp \
            Widgets/connecttoserverdialog.cpp \
            Widgets/commandlinewidget.cpp \
            Engine/configreader.cpp \
            Widgets/previewwindow.cpp \
            Engine/commandlineparser.cpp \
            Widgets/streamselectwidget.cpp \
            Engine/fileEngine.cpp \
            Engine/mediabuffer.cpp \
            DataTypes/ImageTypes/rawimageframe.cpp \
            DataTypes/ImageTypes/abstractimageframe.cpp \
            DataTypes/Parameters/selectparameter.cpp \
            DataTypes/Parameters/numericparameter.cpp \
            DataTypes/Parameters/booleanparameter.cpp \
            DataTypes/Parameters/abstractparameter.cpp \
            Widgets/previewchannel.cpp \
    Widgets/Dialogs/connecttoserverdialog.cpp \
    Widgets/PreviewWidget/previewwindow.cpp \
    Widgets/PreviewWidget/previewchannel.cpp \
    Widgets/ProcessesInputWidgets/streamselectwidget.cpp \
    Widgets/ProcessesInputWidgets/processstepWidget.cpp \
    Widgets/ProcessesInputWidgets/parameterwidget.cpp

HEADERS  += gui.h \
            Widgets/processstepWidget.h \
            Engine/engine.h \
            Widgets/parameterwidget.h \
            DataTypes/processstep.h \
            Engine/dataTransciever.h \
            Widgets/connecttoserverdialog.h \
            Widgets/commandlinewidget.h \
            Engine/configreader.h \
            DataTypes/allparametertypes.h \
            Widgets/previewwindow.h \
            Engine/commandlineparser.h \
            Widgets/streamselectwidget.h \
            Engine/fileEngine.h \
            DataTypes/ClientServerProtocol.h \
            Engine/mediabuffer.h \
            DataTypes/ImageTypes/rawimageframe.h \
            DataTypes/ImageTypes/abstractimageframe.h \
            DataTypes/Parameters/selectparameter.h \
            DataTypes/Parameters/numericparameter.h \
            DataTypes/Parameters/booleanparameter.h \
            DataTypes/Parameters/allparametertypes.h \
            DataTypes/Parameters/abstractparameter.h \
            DataTypes/ImageTypes/allimagetypes.h \
            Widgets/previewchannel.h \
    Widgets/Dialogs/connecttoserverdialog.h \
    Widgets/PreviewWidget/previewwindow.h.autosave \
    Widgets/PreviewWidget/previewwindow.h \
    Widgets/PreviewWidget/previewchannel.h \
    Widgets/ProcessesInputWidgets/streamselectwidget.h \
    Widgets/ProcessesInputWidgets/processstepWidget.h \
    Widgets/ProcessesInputWidgets/parameterwidget.h

FORMS    += gui.ui \
            Widgets/processstepWidget.ui \
            Widgets/parameterwidget.ui \
            Widgets/connecttoserverdialog.ui \
            Widgets/commandlinewidget.ui \
            Widgets/previewwindow.ui \
            Widgets/streamselectwidget.ui \
    Widgets/Dialogs/connecttoserverdialog.ui \
    Widgets/PreviewWidget/previewwindow.ui \
    Widgets/ProcessesInputWidgets/streamselectwidget.ui \
    Widgets/ProcessesInputWidgets/processstepWidget.ui \
    Widgets/ProcessesInputWidgets/parameterwidget.ui

OTHER_FILES += \
            Config/ProcessSteps.xml \
            Graphics/StereoVision.ico \
            Graphics/StereoVisionIcon.rc \
            Graphics/StereoVision.png \
            Documentation/CommandList.html

RESOURCES += \
    Graphics/Graphics.qrc
