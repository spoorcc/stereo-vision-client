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

    this->connect( _dataTransciever, SIGNAL(printToConsole(QString,QString)),SIGNAL(printToConsole(QString,QString)));
    this->connect( _dataTransciever, SIGNAL(xmlDataReceived(QFile*)), SLOT(initProcessSteps(QFile*)));
    _dataTransciever->connect( this, SIGNAL(connectToServer(QHostAddress,quint16)),SLOT(connectToServer(QHostAddress,quint16)));
    _dataTransciever->connect( this, SIGNAL(commandForServer(QString)),SLOT(sendCommand(QString)));
    _dataTransciever->connect( this, SIGNAL(imageForServer(QImage*,int)),SLOT(sendImage(QImage*,int)) );
    _dataTransciever->connect( this, SIGNAL(setValueOnServer(QString,QString,QString)),SLOT(setParameter( QString, QString, QString )));
    _dataTransciever->connect( this, SIGNAL(requestXML()),SLOT(requestXML()));

    _mediaBuffer = new MediaBuffer(this);
    _mediaBuffer->setObjectName("mediaBuffer");
    _mediaBuffer->connect( _dataTransciever, SIGNAL(imageDataReceived(QByteArray)), SLOT(processImageDatagram(QByteArray)));
    this->connect( _mediaBuffer, SIGNAL(imageReceived(QImage,int)), SIGNAL(imageReceived(QImage,int)));

    connect( _mediaBuffer, SIGNAL(print(QString)), SLOT(print(QString)));
}

void Engine::init()
{
    emit ready();
    emit printToConsole("Engine","initialised");
}

void Engine::initProcessSteps( QFile* file)
{    
    emit clearGui();

    _processSteps.clear();

    if( file == 0)
    {
        _configReader->parseXmlFile( CONFIG_FILE );
    }
    else
    {
        _configReader->parseXmlFile( file );
    }
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
    int streamID = getStreamId( processStep, streamName);

    subscribePreviewChannelToStream( previewChannel, streamID, continous);
}
void Engine::subscribePreviewChannelToStream(int previewChannel,int streamID, bool continous)
{
    //Let the previewchannel listen to the correct buffer
    _mediaBuffer->subscribeChannelToStream( previewChannel, streamID );

    //Ask the server for the image
    _dataTransciever->getImage( streamID, continous);
}
void Engine::replaceStream(QString processStep, QString streamName, QImage* image)
{
    int streamId = getStreamId(processStep, streamName);
    emit imageForServer(image, streamId);
}

void Engine::flushImageBuffers()
{
    _mediaBuffer->flushBuffers();
}
int Engine::getStreamId( QString processStep, QString streamName )
{
    //Test image id
    if( processStep == "test_image" && streamName == "test_image" )
    {
        return clientServerProtocol::TEST_STREAM;
    }

    //Start at 1 because 0 is test stream
    int streamID = clientServerProtocol::CAMERA_1;

    // !-- First 8 streams are defined as camera_1 to camera_8 --!

    foreach( ProcessStep* step, _processSteps)
    {
        if( step->name() == processStep )
        {
            streamID += step->streamID( streamName );
            break;
        }
        streamID += step->numberOfStreams();
    }

    return streamID;
}

void Engine::addParsedProcessStep(ProcessStep *processStep)
{
    _processSteps.append( processStep );

    //To let engine have easy access to processsteps name the object and let parent have it
    processStep->setObjectName( processStep->name() );
    processStep->setParent( this );

    emit addProcessStep( processStep );

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

