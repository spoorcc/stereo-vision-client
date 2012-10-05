#include "engine.h"

Engine::Engine(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType< ProcessStep*  >( "ProcessStepPointer" );

    _configReader = new ConfigReader(this);
    this->connect( _configReader, SIGNAL(parsedNewProcessStep(ProcessStep*)), SLOT(addParsedProcessStep(ProcessStep*)));
    this->connect( _configReader, SIGNAL(parsingFailed(QString)), SLOT(parsingFailed(QString)));
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
    emit printToConsole("Engine", "Initialised process step " + processStep->name() );
}
void Engine::parsingFailed( QString message)
{
    emit printToConsole("Engine", "Parsing failed :" + message);
}
