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

// Local includes
#include "DataTypes/allparametertypes.h"
#include "DataTypes/processstep.h"

#include "configreader.h"
#include "commandlineparser.h"

#ifdef _WIN32
    #define CONFIG_FILE "D:\\QTgui\\ProcessSteps.xml"
    //#define CONFIG_FILE "D:\\Documents\\School\\Avans\\4.1_MESD\\StereoVisionQT\\Config\\ProcessSteps.xml"
#elif __linux
    #define CONFIG_FILE "/home/ben/Programming/Avans/stereo-vision-client/trunk/Config/ProcessSteps.xml"
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
    void commandForServer( QString command );

public slots:
    void giveProcessSteps();
    void parseCommand( QString command );

private slots:
    void addParsedProcessStep( ProcessStep* processStep );
    void configParsingFailed(QString message);

    void commandParseStatus(QString message, bool succesfull);

    void sendCommandForServer( QString command );

private:
    void initProcessSteps();

    QList< ProcessStep* > _processSteps;
    ConfigReader* _configReader;
    CommandLineParser* _commandLineParser;

};

Q_DECLARE_METATYPE( ProcessStep* )

#endif // ENGINE_H
