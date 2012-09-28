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
    //TODO: Eventually this should be done from a xml-file for more flexability

    ProcessStep* cameras = new ProcessStep("Camera 0",0,this);

    ProcessStep* calibration = new ProcessStep("Calibration",4,this);
    ProcessStep* rectification = new ProcessStep("Rectification",5,this);
    ProcessStep* stereoMatching = new ProcessStep("Stereo matching", 6, this);

    BooleanParameter* oneShot = new BooleanParameter("OneShot",true);
    BooleanParameter* enabled = new BooleanParameter("Enabled");
    BooleanParameter* maurice = new BooleanParameter("Maurice betaalt de koffie",true);

    NumericParameter* hSize = new NumericParameter( "hSize", 480, 240, 1080 );
    NumericParameter* vSize = new NumericParameter( "vSize", 640, 320, 1920 );

    SelectParameter* cameraSelection = new SelectParameter( "Select camera's");
    cameraSelection->addOption( "Camera 1 & 2");
    cameraSelection->addOption( "Camera 1 & 3");
    cameraSelection->addOption( "Camera 1 & 4");
    cameraSelection->addOption( "Camera 2 & 3");
    cameraSelection->addOption( "Camera 2 & 4");
    cameraSelection->addOption( "Camera 3 & 4");

    cameraSelection->addOption( "Camera 5 & 6");
    cameraSelection->addOption( "Camera 5 & 7");
    cameraSelection->addOption( "Camera 5 & 8");
    cameraSelection->addOption( "Camera 6 & 7");
    cameraSelection->addOption( "Camera 6 & 8");
    cameraSelection->addOption( "Camera 7 & 8");

    cameras->addParameter( cameraSelection );
    cameras->addParameter( oneShot );
    cameras->addParameter( enabled );
    cameras->addParameter( hSize );
    cameras->addParameter( vSize );

    _processSteps.append( cameras );
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
