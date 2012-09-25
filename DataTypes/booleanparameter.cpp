#include "booleanparameter.h"

BooleanParameter::BooleanParameter()
{
}

bool BooleanParameter::isBoolean() const
{
    return true;
}

bool BooleanParameter::isNumerical() const
{
    return false;
}

//Get methods;
bool BooleanParameter::isEnabled() const
{
    return _state;
}

bool BooleanParameter::isDisabled() const
{
    return !_state;
}

// Set methods
void BooleanParameter::setEnabled()
{
    if( !_state )
    {
        _state = true;
        emit valueChanged();
    }
}

void BooleanParameter::setDisabled()
{
    if( _state )
    {
        _state = false;
        emit valueChanged();
    }
}

void BooleanParameter::set(bool state)
{
    _state = state;
    emit valueChanged();
}

void BooleanParameter::toggle()
{
    _state = !_state;
    emit valueChanged();
}

void BooleanParameter::update(AbstractParameter *parameter)
{
    //Check if parameter is boolean
    if( !parameter->isBoolean() )
    {
        emit illegalUpdate();
        return;
    }
    else
    {
        //Convert to boolean pointer and copy the info
        _state = ( (BooleanParameter*) parameter)->isEnabled();

        emit valueChanged();
    }
}
