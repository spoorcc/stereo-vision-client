#ifndef ENGINE_H
#define ENGINE_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The engine is the main object which keeps all data about the process.

*/

// Global includes
#include <QObject>

// Local includes
#include "DataTypes/booleanparameter.h"
#include "DataTypes/numericparameter.h"

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // ENGINE_H
