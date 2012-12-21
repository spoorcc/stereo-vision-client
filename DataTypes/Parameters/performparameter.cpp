#include "performparameter.h"

PerformParameter::PerformParameter( QString name, bool fireOnInit )
{
    setName( name );
    _fireOnInit = fireOnInit;

    if( fireOnInit )
    {
        emit valueChanged();
    }
}

bool PerformParameter::isPerform() const
{
    return true;
}

bool PerformParameter::fireOnInit()
{
    return _fireOnInit;
}

void PerformParameter::perform()
{
    emit valueChanged();
}

void PerformParameter::setFireOnInit(QString value)
{
}

void PerformParameter::update(AbstractParameter *parameter)
{
    //Check if parameter is numerical
    if( !parameter->isPerform() )
    {
        emit illegalUpdate();
        return;
    }
    else
    {
        //Convert into numeric pointer and copy the info
        _fireOnInit = ( (PerformParameter*) parameter)->fireOnInit();

        if( fireOnInit() )
        {
            emit valueChanged();
        }
    }
}
