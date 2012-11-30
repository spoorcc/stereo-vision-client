#ifndef CONFIGREADER_H
#define CONFIGREADER_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The configreader opens a XML file and parses the content. It sends it results to the engine

*/

// Global includes
#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QMap>

// Local includes
#include "DataTypes/Parameters/allparametertypes.h"
#include "DataTypes/processstep.h"

#include "DataTypes/ClientServerProtocol.h"

class ConfigReader : public QObject
{
    Q_OBJECT
public:
    explicit ConfigReader(QObject *parent = 0);

signals:
    void startedParsing();
    void invalidFilePath();

    void configParsingFailed( QString message );
    void parsingSuccesfull();
    void parsedNewProcessStep( ProcessStep* step );

public slots:
    void parseXmlFile( QString path );

private:    
    void parseProcessStep(QXmlStreamReader &xml);

    BooleanParameter* parseBooleanParameter(QXmlStreamReader &xml);
    NumericParameter* parseNumericParameter(QXmlStreamReader &xml );
    SelectParameter*  parseSelectParameter( QXmlStreamReader &xml );

    bool checkAttribute(QXmlStreamAttributes &attributes, QString attributeType, QString attributeValue);

    int _streamID;
};

#endif // CONFIGREADER_H
