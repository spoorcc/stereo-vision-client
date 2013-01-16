#include "configreader.h"

ConfigReader::ConfigReader(QObject *parent) :
    QObject(parent)
{
}
void ConfigReader::parseXmlFile( QString path )
{
    /* We'll parse the example.xml */
    QFile* file = new QFile( path );

    parseXmlFile( file );
}

void ConfigReader::parseXmlFile( QFile* file )
{
    emit startedParsing();

    _streamID = clientServerProtocol::CAMERA_1;

    //Try to open it
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        emit configParsingFailed( "Couldn't open file " + file->fileName() );
        return;
    }

    QXmlStreamReader xml(file);

    /* We'll parse the XML until we reach end of it.*/
    while(!xml.atEnd() && !xml.hasError())
    {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = xml.readNext();

        /* If token is just StartDocument, we'll go to next.*/
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement) {
        /* If it's named processstep, we'll go to the next.*/
            if(xml.name() == "processstep")
            {
                parseProcessStep(xml);
                continue;
            }
        }
    }

    /* Error handling. */
    if(xml.hasError())
    {
        emit configParsingFailed( "There was error in the xml file");
    }

    /* Removes any device() or data from the reader
         * and resets its internal state to the initial state. */
    xml.clear();

}
bool ConfigReader::checkAttribute( QXmlStreamAttributes& attributes, QString attributeType, QString attributeValue )
{
    if( attributes.hasAttribute( attributeType ) )
    {
        QString value =  attributes.value( attributeType ).toString();

        return (0 == QString::compare( value, attributeValue ) );
    }

    //If attribute doesn't exist
    return 0;
}
void ConfigReader::parseProcessStep( QXmlStreamReader& xml)
{
    QXmlStreamAttributes attributes = xml.attributes();

    QString name = QString( attributes.value("name").toString() );
    QString group = QString( attributes.value("group").toString() );
    QString color = QString( attributes.value("color").toString() );

    QColor colorToSet;
    QStringList rgb = color.split(",");

    if( rgb.count() == 3)
    {
        colorToSet = QColor( rgb.at(0).toInt(), rgb.at(1).toInt(), rgb.at(2).toInt() );
    }
    else
    {
        colorToSet = QColor( color );
    }

    ProcessStep* step = new ProcessStep( name, 0, group, colorToSet );     

    //Read until end of processtep
    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "processstep"))
    {        
        xml.readNext();

        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if( xml.name() == "parameter")
            {
                QXmlStreamAttributes parameterAttributes = xml.attributes();
                if( checkAttribute(parameterAttributes, QString("type"), QString("boolean")))
                {
                    step->addParameter( this->parseBooleanParameter( xml ) );
                }
                if( checkAttribute(parameterAttributes, QString("type"), QString("numeric")))
                {
                    step->addParameter( this->parseNumericParameter( xml ) );
                }
                if( checkAttribute(parameterAttributes, QString("type"), QString("selectable")))
                {
                    step->addParameter( this->parseSelectParameter( xml ) );
                }
                if( checkAttribute(parameterAttributes, QString("type"), QString("perform")))
                {
                    step->addParameter( this->parsePerformParameter( xml ) );
                }
            }
            if (xml.name()== "stream")
            {
                QXmlStreamAttributes streamAttributes = xml.attributes();

                xml.readNext();

                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "stream"))
                {
                    if(xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if(xml.name() == "substream")
                        {
                           bool isInput = checkAttribute(streamAttributes, QString("type"), QString("input"));
                           step->addStream(xml.readElementText(), isInput);
                        }
                    }
                    xml.readNext();
                }
            }
        }
        if(xml.tokenType() == QXmlStreamReader::Invalid )
        {
            return;
        }
        if( xml.isWhitespace() )
        {
            continue;
        }
    }

    emit parsedNewProcessStep( step );

}

BooleanParameter* ConfigReader::parseBooleanParameter( QXmlStreamReader& xml)
{
    QXmlStreamAttributes attributes = xml.attributes();

    if( !checkAttribute(attributes, "type", "boolean" ) )
    {
        return 0;
    }

    QString name = xml.attributes().value("name").toString();
    QString init = xml.attributes().value("init").toString();
    bool value = false;

    if( QString::compare( init, "enabled") == 0 ||
        QString::compare( init, "enable" ) == 0 ||
        QString::compare( init, "true")== 0)
    {
        value = true;
    }

    BooleanParameter* parameter = new BooleanParameter(name, value);

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "parameter"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "description")
            {
                parameter->setDesciption( xml.readElementText() );
            }
        }
        xml.readNext();
    }

    return parameter;
}

NumericParameter *ConfigReader::parseNumericParameter( QXmlStreamReader& xml )
{
    QXmlStreamAttributes attributes = xml.attributes();

    if( !checkAttribute(attributes, "type", "numeric" ) )
    {
        return 0;
    }

    QString name = xml.attributes().value("name").toString();
    QString min  = xml.attributes().value("min").toString();
    QString init = xml.attributes().value("init").toString();
    QString max  = xml.attributes().value("max").toString();

    NumericParameter* parameter = new NumericParameter(name, init.toInt(), min.toInt(), max.toInt() );

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "parameter"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "description")
            {
                parameter->setDesciption( xml.readElementText() );
            }
        }
        xml.readNext();
    }

    return parameter;

}
SelectParameter* ConfigReader::parseSelectParameter( QXmlStreamReader& xml )
{
    QXmlStreamAttributes attributes = xml.attributes();

    if( !checkAttribute(attributes, "type", "selectable" ) )
    {
        return 0;
    }

    QString name = xml.attributes().value("name").toString();

    SelectParameter* parameter = new SelectParameter(name);

    xml.readNext();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "parameter"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "option")
            {
               parameter->addOption( xml.readElementText() );
            }
            if(xml.name() == "description")
            {
                parameter->setDesciption( xml.readElementText() );
            }
        }
        xml.readNext();
    }

    return parameter;
}
PerformParameter* ConfigReader::parsePerformParameter( QXmlStreamReader& xml )
{
    QXmlStreamAttributes attributes = xml.attributes();

    if( !checkAttribute(attributes, "type", "perform" ) )
    {
        return 0;
    }

    QString name = xml.attributes().value("name").toString();
    QString fireOnInit = xml.attributes().value("name").toString();

    bool fire = ( fireOnInit == "true" );

    PerformParameter* parameter = new PerformParameter(name, fire);

    xml.readNext();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "parameter"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {

            if(xml.name() == "description")
            {
                parameter->setDesciption( xml.readElementText() );
            }
        }
        xml.readNext();
    }

    return parameter;
}
