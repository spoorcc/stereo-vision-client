#ifndef CONFIGREADER_H
#define CONFIGREADER_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The configreader opens a XML file and parses the content. It sends it results to the engine

*/

// Global includes
#include <QObject>

// Local includes
#include "DataTypes/allparametertypes.h"
#include "DataTypes/processstep.h"

class ConfigReader : public QObject
{
    Q_OBJECT
public:
    explicit ConfigReader(QObject *parent = 0);
    
signals:
    void startedParsing();
    void invalidFilePath();

    void parsingFailed();
    void parsingSuccesfull();
    void parsedNewProcessStep( ProcessStep* step );

public slots:
    void parseXmlFile( QString path );

private:

};

#endif // CONFIGREADER_H
