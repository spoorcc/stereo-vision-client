#include "numericparameter.h"

NumericParameter::NumericParameter(QString name, int init, int min, int max)
{
    setName( name );
    setInit( init );
    setMinimum( min );
    setMaximum( max );
}

bool NumericParameter::isNumerical() const
{
    return true;
}

//------------------------------------------------------------------
// Get methods

int NumericParameter::minimum() const
{
    return _minimum;
}
int NumericParameter::init() const
{
    return _init;
}

int NumericParameter::value() const
{
    return _value;
}

int NumericParameter::maximum() const
{
    return _maximum;
}

//--------------------------------------------------------------------
// Set methods

void NumericParameter::setMinimum(int minimum)
{
    _minimum = minimum;
    emit valueChanged();
}

void NumericParameter::setInit(int init)
{
    _init = init;
    emit valueChanged();
}
void NumericParameter::setValue(int value)
{
    _value = value;
    emit valueChanged();
}

void NumericParameter::setMaximum(int maximum)
{
    _maximum = maximum;
    emit valueChanged();
}

void NumericParameter::update(AbstractParameter *parameter)
{
    //Check if parameter is numerical
    if( !parameter->isNumerical() )
    {
        emit illegalUpdate();
        return;
    }
    else
    {
        //Convert into numeric pointer and copy the info
        _minimum = ( (NumericParameter*) parameter)->minimum();
        _value   = ( (NumericParameter*) parameter)->value();
        _maximum = ( (NumericParameter*) parameter)->maximum();

        emit valueChanged();
    }

}
