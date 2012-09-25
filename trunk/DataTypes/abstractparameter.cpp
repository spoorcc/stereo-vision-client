#include "abstractparameter.h"

AbstractParameter::AbstractParameter(QObject *parent) :
    QObject(parent)
{
}

void AbstractParameter::setName(QString name)
{
    _name = name;
}
