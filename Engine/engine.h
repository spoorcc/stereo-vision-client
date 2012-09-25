#ifndef ENGINE_H
#define ENGINE_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The engine is the main object which keeps all data about the process.

*/

// Global includes
#include <QObject>
#include <QMetaType>

// Local includes
#include "DataTypes/booleanparameter.h"
#include "DataTypes/numericparameter.h"
#include "DataTypes/processstep.h"

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);

    int numberOfSteps() const;
    
signals:
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
