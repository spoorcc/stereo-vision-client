#include "configreader.h"

ConfigReader::ConfigReader(QObject *parent) :
    QObject(parent)
{
}
void ConfigReader::parseXmlFile( QString path )
{
    emit startedParsing();

    //Open the file


    //Search for all the processSteps

    //Look for every parameter in the procesStep

    //emit the new processStep
}
