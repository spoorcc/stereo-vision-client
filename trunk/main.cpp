/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:

*/

// Global includes
#include <QtGui/QApplication>

// Local includes
#include "gui.h"
#include "Engine/engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI* gui = new GUI();
    Engine* engine = new Engine();

    engine->connect( gui, SIGNAL(needAllProcessSteps()), SLOT( giveProcessSteps() ) );

    gui->connect( engine, SIGNAL( addProcessStep(ProcessStep*) ), SLOT( addProcessStep(ProcessStep*) ) );
    gui->connect( engine, SIGNAL( printToConsole(QString, QString) ), SLOT( printToConsole(QString, QString) ) );
    gui->show();
    
    return a.exec();
}
