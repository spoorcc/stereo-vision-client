#include "abstractparameter.h"

AbstractParameter::AbstractParameter(QObject *parent) :
    QObject(parent)
{
}

void AbstractParameter::setName(QString name)
{
    _name = name;
}

void AbstractParameter::setDesciption(QString description)
{
    _description = description;
}

QString AbstractParameter::name() const
{
    return _name;
}
QString AbstractParameter::description() const
{
    return _description;
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
