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

// Local includes
#include "DataTypes/allparametertypes.h"
#include "DataTypes/processstep.h"

#include "configreader.h"

#ifdef _WIN32
    #define CONFIG_FILE "D:\\QTgui\\trunk\\Config\\ProcessSteps.xml"
#else
    #define CONFIG_FILE "home/ben/Programming/Avans/stereo-vision-client/trunk/Config/ProcessSteps.xml"
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

public slots:
    void giveProcessSteps();

private slots:
    void addParsedProcessStep( ProcessStep* processStep );
    void parsingFailed(QString message);

private:
    void initProcessSteps();

    QList< ProcessStep* > _processSteps;
    ConfigReader* _configReader;
    
};

Q_DECLARE_METATYPE( ProcessStep* )

#endif // ENGINE_H
