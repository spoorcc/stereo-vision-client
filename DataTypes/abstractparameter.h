#ifndef ABSTRACTPARAMETER_H
#define ABSTRACTPARAMETER_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  This class is an abstract class and can therefore not be instantiated.It contains the methods, signals and slots that both numerical as boolean parameters have in common.

*/

// Global includes
#include <QObject>

class AbstractParameter : public QObject
{
    Q_OBJECT
public:
    explicit AbstractParameter(QObject *parent = 0);

    //Set-methods
    void setName( QString name );

    //Get-methods
    virtual bool isBoolean() = 0;       //This methods must be specified in derived classes
    virtual bool isNumerical() = 0;     //This methods must be specified in derived classes
    
signals:
    
    void valueChanged();

public slots:

private:
    QString _name;
    
};

#endif // ABSTRACTPARAMETER_H
