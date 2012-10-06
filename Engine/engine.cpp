#include "engine.h"

Engine::Engine(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType< ProcessStep*  >( "ProcessStepPointer" );

    _configReader = new ConfigReader(this);

    this->connect( _configReader, SIGNAL(parsedNewProcessStep(ProcessStep*)), SLOT(addParsedProcessStep(ProcessStep*)));
    this->connect( _configReader, SIGNAL(configParsingFailed(QString)), SLOT(configParsingFailed(QString)));

    _commandLineParser = new CommandLineParser(this);
    this->connect( _commandLineParser, SIGNAL(commandParseError(QString)),SLOT(commandParseStatus(QString)));
    this->connect( _commandLineParser, SIGNAL(commandParseSucces(QString)), SLOT(commandParseStatus(QString)) );

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

void Engine::parseCommand(QString command)
{
    _commandLineParser->parseCommand( command );
}

void Engine::addParsedProcessStep(ProcessStep *processStep)
{
    _processSteps.append( processStep );
    emit printToConsole("Engine", "Initialised process step " + processStep->name() );
}
void Engine::configParsingFailed( QString message)
{
    emit printToConsole("Engine", "Parsing failed :" + message);
}
void Engine::commandParseStatus( QString message )
{
    emit printToConsole("Engine", message );
}
