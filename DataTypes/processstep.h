#ifndef PROCESSSTEP_H
#define PROCESSSTEP_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  This class holds all the data of a processstep.

*/

// Global includes
#include <QObject>
#include <QStringList>

//Local includes
#include "DataTypes/allparametertypes.h"

class ProcessStep : public QObject
{
    Q_OBJECT
public:
    explicit ProcessStep(QString name, int number, QString group, QString color = "white", QObject *parent = 0);
    
    //Get methods
    QString name();
    QString group();
    QString color();

    QStringList inputStreams();
    QStringList outputStreams();

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

    void addStream( QString streamname, bool isInput);

    void changeParameter( AbstractParameter* parameter );
    void parameterChanged();

private:
    QString _name;
    int _stepNumber;
    QString _group;
    QString _color;

    QStringList _inputStreams;
    QStringList _outputStreams;

    QList< AbstractParameter* > _parameters;

    void addParameter( AbstractParameter* parameter );

};

#endif // PROCESSSTEP_H
