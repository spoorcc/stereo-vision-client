#include "engine.h"

Engine::Engine(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType< ProcessStep*  >( "ProcessStepPointer" );

    _configReader = new ConfigReader(this);
    _configReader->setObjectName("configReader");

    this->connect( _configReader, SIGNAL(parsedNewProcessStep(ProcessStep*)), SLOT(addParsedProcessStep(ProcessStep*)));
    this->connect( _configReader, SIGNAL(configParsingFailed(QString)), SLOT(configParsingFailed(QString)));

    _dataTransciever = new DataTransciever(this);
    _dataTransciever->setObjectName("dataTransciever");

    _mediaBuffer = new MediaBuffer(this);
    _mediaBuffer->setObjectName("mediaBuffer");
    _mediaBuffer->connect( _dataTransciever, SIGNAL(imageDataReceived(QByteArray)), SLOT(processImageDatagram(QByteArray)));

    connect( _mediaBuffer, SLOT(print(QString)), SLOT(print(QString)));
}

void Engine::init()
{
    initProcessSteps();
    emit ready();
    emit printToConsole("Engine","initialised");
}

void Engine::initProcessSteps()
{    
    _configReader->parseXmlFile( CONFIG_FILE );
}


void Engine::giveProcessSteps()
{
    foreach( ProcessStep* processStep, _processSteps)
    {
        emit addProcessStep( processStep );
    }
}

void Engine::subscribePreviewChannelToStream(int previewChannel, QString processStep, QString streamName, bool continous)
{
    //Start at 1 because 0 is test stream
    int streamID = 1;

    foreach( ProcessStep* step, _processSteps)
    {
        if( step->name() == processStep )
        {
            streamID += step->streamID( streamName );
            break;
        }
        streamID += step->numberOfStreams();
    }

    subscribePreviewChannelToStream( previewChannel, streamID, continous);
}
void Engine::subscribePreviewChannelToStream(int previewChannel,int streamID, bool continous)
{
    //Let the previewchannel listen to the correct buffer
    _mediaBuffer->subscribeChannelToStream( previewChannel, streamID );

    //Ask the server for the image
    _dataTransciever->getImage( streamID, continous);
}
void Engine::addParsedProcessStep(ProcessStep *processStep)
{
    _processSteps.append( processStep );

    //To let engine have easy access to processsteps name the object and let parent have it
    processStep->setObjectName( processStep->name() );
    processStep->setParent( this );

    emit print( "Initialised process step " + processStep->name() );
}
void Engine::configParsingFailed( QString message)
{
    emit printToConsole("Engine", "Parsing failed :" + message);
}

void Engine::print( QString message )
{
    emit printToConsole("Engine", message);
}

