#include "engine.h"

Engine::Engine(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType< ProcessStep*  >( "ProcessStepPointer" );
}

void Engine::init()
{
    initProcessSteps();
    emit ready();
    emit printToConsole("Engine","initialised");
}

void Engine::initProcessSteps()
{
    ProcessStep* camera0 = new ProcessStep("Camera 0",0,this);
    ProcessStep* camera1 = new ProcessStep("Camera 1",1,this);
    ProcessStep* camera2 = new ProcessStep("Camera 2",2,this);
    ProcessStep* camera3 = new ProcessStep("Camera 3",3,this);

    ProcessStep* calibration = new ProcessStep("Calibration",4,this);
    ProcessStep* rectification = new ProcessStep("Rectification",5,this);
    ProcessStep* stereoMatching = new ProcessStep("Stereo matching", 6, this);

    BooleanParameter* oneShot = new BooleanParameter("OneShot",true);
    BooleanParameter* enabled = new BooleanParameter("Enabled");
    NumericParameter* hSize = new NumericParameter( "hSize", 480, 240, 1080 );
    NumericParameter* vSize = new NumericParameter( "vSize", 640, 320, 1920 );

    camera0->addParameter( oneShot );
    camera0->addParameter( enabled );
    camera0->addParameter( hSize );
    camera0->addParameter( vSize );

    _processSteps.append( camera0 );
    _processSteps.append( camera1 );
    _processSteps.append( camera2 );
    _processSteps.append( camera3 );
    _processSteps.append( calibration );
    _processSteps.append( rectification );
    _processSteps.append( stereoMatching );
}

void Engine::giveProcessSteps()
{
    foreach( ProcessStep* processStep, _processSteps)
    {
        emit addProcessStep( processStep );
    }
}
