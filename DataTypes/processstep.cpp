#include "processstep.h"

ProcessStep::ProcessStep(QString name, int number, QString group, QObject *parent) :
    QObject(parent)
{
        _name = name;
        _stepNumber = number;
        _group = group;
}

QString ProcessStep::name()
{
    return _name;
}
QString ProcessStep::group()
{
    return _group;
}

AbstractParameter* ProcessStep::parameter(QString name)
{
    foreach( AbstractParameter* parameter, _parameters )
    {
        if( parameter->isBoolean() )
        {

        }
        if( QString::compare( parameter->AbstractParameter::name() , name, Qt::CaseInsensitive ) == 0 )
        {
            return parameter;
        }
    }

    //FIXME: If no matching parameter is found, a nullpointer will crash the program
    return 0;
}

AbstractParameter* ProcessStep::parameter(int i)
{
    return _parameters.at(i);
}
int ProcessStep::numberOfParameters() const
{
    return _parameters.count();
}

void ProcessStep::addParameter(BooleanParameter *parameter)
{
    addParameter( (AbstractParameter*) parameter );
}

void ProcessStep::addParameter(NumericParameter *parameter)
{
    addParameter( (AbstractParameter*) parameter );
}
void ProcessStep::addParameter(SelectParameter *parameter)
{
    addParameter( (AbstractParameter*) parameter );
}

void ProcessStep::addParameter(AbstractParameter *parameter)
{
        _parameters.append( parameter );

        //Connect the value changed signal, so when a parameter is succesfully updated the processStep knows it has changed
        this->connect( parameter, SIGNAL(valueChanged()),this, SLOT(parameterChanged()) );
}

void ProcessStep::changeParameter(AbstractParameter *parameter)
{
    foreach( AbstractParameter* localParameter, _parameters )
    {
        if( QString::compare( localParameter->AbstractParameter::name(), parameter->AbstractParameter::name(), Qt::CaseInsensitive ) == 0 )
        {
            localParameter->update( parameter );
        }
    }
}

void ProcessStep::parameterChanged()
{
    emit changedParameter();
}




