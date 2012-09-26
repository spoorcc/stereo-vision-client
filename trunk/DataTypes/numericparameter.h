#ifndef NUMERICPARAMETER_H
#define NUMERICPARAMETER_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  This class extends he abstract class with specific numeric methods and member variables

*/

// Local includes
#include "abstractparameter.h"


class NumericParameter : public AbstractParameter
{
public:
    NumericParameter( QString name, int init = 1, int min = 0, int max = 2 );

    //Get methods
    bool isNumerical() const;

    int minimum() const;
    int init() const;
    int value() const;
    int maximum() const;

public slots:

    //Set methods
    void setMinimum( int minimum );
    void setInit( int init );
    void setValue( int value );
    void setMaximum( int maximum );

    void update(AbstractParameter *parameter);

private:
    int _minimum;
    int _init;
    int _value;
    int _maximum;
};

#endif // NUMERICPARAMETER_H
