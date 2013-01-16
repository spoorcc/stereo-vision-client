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
            Engine/engine.cpp \
            DataTypes/processstep.cpp \
            Widgets/commandlinewidget.cpp \
            Engine/configreader.cpp \
            Engine/fileEngine.cpp \
            Engine/mediabuffer.cpp \
            DataTypes/ImageTypes/rawimageframe.cpp \
            DataTypes/ImageTypes/abstractimageframe.cpp \
            DataTypes/Parameters/selectparameter.cpp \
            DataTypes/Parameters/numericparameter.cpp \
            DataTypes/Parameters/booleanparameter.cpp \
            DataTypes/Parameters/abstractparameter.cpp \
            Widgets/Dialogs/connecttoserverdialog.cpp \
            Widgets/PreviewWidget/previewwindow.cpp \
            Widgets/PreviewWidget/previewchannel.cpp \
            Widgets/ProcessesInputWidgets/streamselectwidget.cpp \
            Widgets/ProcessesInputWidgets/processstepWidget.cpp \
            Widgets/ProcessesInputWidgets/parameterwidget.cpp \
            Engine/DataTransciever/dataTransciever.cpp \
            Engine/DataTransciever/datasendsocket.cpp \
            Engine/DataTransciever/datareceivesocket.cpp \
    DataTypes/ImageTypes/jpegimageframe.cpp \
    DataTypes/Parameters/performparameter.cpp

HEADERS  += gui.h \
            Engine/engine.h \
            DataTypes/processstep.h \
            Widgets/commandlinewidget.h \
            Engine/configreader.h \
            DataTypes/allparametertypes.h \
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
            Widgets/Dialogs/connecttoserverdialog.h \
            Widgets/PreviewWidget/previewwindow.h \
            Widgets/PreviewWidget/previewchannel.h \
            Widgets/ProcessesInputWidgets/streamselectwidget.h \
            Widgets/ProcessesInputWidgets/processstepWidget.h \
            Widgets/ProcessesInputWidgets/parameterwidget.h \
            Widgets/PreviewWidget/previewwindowconfig.h \
            Engine/DataTransciever/dataTransciever.h \
            Engine/DataTransciever/datasendsocket.h \
            Engine/DataTransciever/datareceivesocket.h \
    DataTypes/ImageTypes/jpegimageframe.h \
    DataTypes/Parameters/performparameter.h

FORMS    += gui.ui \
            Widgets/commandlinewidget.ui \
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
            Documentation/CommandList.html \
    Graphics/down_arrow.ico

RESOURCES += \
    Graphics/Graphics.qrc
