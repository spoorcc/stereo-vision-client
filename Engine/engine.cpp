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

void Engine::addParsedProcessStep(ProcessStep *processStep)
{
    _processSteps.append( processStep );
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

