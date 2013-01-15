#ifndef ENGINE_H
#define ENGINE_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The engine is the main object which keeps all data about the process.

*/

#define CONFIG_PATH /conf/processStep.xml

// Global includes
#include <QObject>
#include <QMetaType>
#include <QDesktopServices>
#include <QDebug>

// Local includes
#include "DataTypes/Parameters/allparametertypes.h"
#include "DataTypes/processstep.h"

#include "Engine/DataTransciever/dataTransciever.h"
#include "Engine/mediabuffer.h"
#include "Engine/configreader.h"

#ifdef _WIN32
    #define CONFIG_FILE "D:\\QTgui\\ProcessSteps.xml"
    //#define CONFIG_FILE "D:\\Documents\\School\\Avans\\4.1_MESD\\StereoVisionQT\\Config\\ProcessSteps.xml"
#elif __linux
    #define CONFIG_FILE "/home/ben/Programming/WORKING_COPIES/trunk/Config/ProcessSteps.xml"
#endif

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);

    void init();
    int numberOfSteps() const;

signals:
    void ready();
    void printToConsole( QString sender, QString message );
    void addProcessStep( ProcessStep* processStep);

    void connectToServer( QHostAddress address, quint16 port );
    void commandForServer( QString command );
    void imageForServer(QImage*, int);

    void imageReceived(QImage,int);

public slots:
    void giveProcessSteps();

    void subscribePreviewChannelToStream(int previewChannel, QString procesStep, QString streamName, bool continous);
    void subscribePreviewChannelToStream(int previewChannel, int streamID, bool continous);

    void replaceStream(QString processStep, QString streamName, QImage *image);

private slots:
    void print(QString message);
    void addParsedProcessStep( ProcessStep* processStep );
    void configParsingFailed(QString message);

private:
    void initProcessSteps();
    int getStreamId(QString processStep, QString streamName);

    QList< ProcessStep* > _processSteps;

    DataTransciever* _dataTransciever;
    ConfigReader* _configReader;
    MediaBuffer* _mediaBuffer;
};

Q_DECLARE_METATYPE( ProcessStep* )

#endif // ENGINE_H
