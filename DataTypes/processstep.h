#ifndef PROCESSSTEP_H
#define PROCESSSTEP_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  This class holds all the data of a processstep.

*/

// Global includes
#include <QObject>

//Local includes
#include "abstractparameter.h"
#include "numericparameter.h"
#include "booleanparameter.h"
#include "selectparameter.h"

class ProcessStep : public QObject
{
    Q_OBJECT
public:
    explicit ProcessStep(QString name, int number, QString group, QObject *parent = 0);
    
    //Get methods
    QString name();
    QString group();

    AbstractParameter* parameter( QString name );
    AbstractParameter* parameter( int i );
    int numberOfParameters() const;

signals:
    void changedParameter();
    
public slots:

    //Set methods
    void addParameter( BooleanParameter* parameter );
    void addParameter( NumericParameter* parameter );
    void addParameter( SelectParameter* parameter );

    void changeParameter( AbstractParameter* parameter );
    void parameterChanged();

private:
    QString _name;
    int _stepNumber;
    QString _group;

    QList< AbstractParameter* > _parameters;

    void addParameter( AbstractParameter* parameter );

};

#endif // PROCESSSTEP_H
