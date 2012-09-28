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

private:
    void initProcessSteps();

    QList< ProcessStep* > _processSteps;
    
};

Q_DECLARE_METATYPE( ProcessStep* )

#endif // ENGINE_H
