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
#include "Engine/dataTransciever.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Engine engine;
    DataTransciever dataTransciever;
    GUI gui;

    engine.connect( &gui, SIGNAL( needAllProcessSteps() ), SLOT( giveProcessSteps() ) );

    gui.connect( &engine, SIGNAL( ready() ), SLOT( start() ));
    gui.connect( &engine, SIGNAL( addProcessStep(ProcessStep*) ), SLOT( addProcessStep(ProcessStep*) ) );


    gui.connect( &engine, SIGNAL( printToConsole(QString, QString) ), SLOT( printToConsole(QString, QString) ) );
    gui.connect( &dataTransciever, SIGNAL(printToConsole( QString, QString)), SLOT( printToConsole(QString, QString) ) );
    gui.show();

    engine.init();
    
    return a.exec();
}
