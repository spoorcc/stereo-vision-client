#include "abstractparameter.h"

AbstractParameter::AbstractParameter(QObject *parent) :
    QObject(parent)
{
}

void AbstractParameter::setName(QString name)
{
    _name = name;
}

QString AbstractParameter::name() const
{
    return _name;
}

bool AbstractParameter::isBoolean() const
{
    return false;
}

bool AbstractParameter::isNumerical() const
{
    return false;
}

bool AbstractParameter::isSelect() const
{
    return false;
}
