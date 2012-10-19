/*
 Project: Stereo-vision-client
 Author: Ben
 Description:

*/

// Global includes
#include <QtGui/QApplication>

// Local includes
#include "gui.h"
#include "Engine/engine.h"
#include "Engine/dataTransciever.h"
#include "Engine/fileEngine.h"

#ifndef _WIN32
 #ifndef __linux__
  #error You are using a mac, it is not iStereoVision, go sue somebody!
 #endif
#endif

int main( int argc, char *argv[] )
{
 QApplication a( argc, argv ) ;

 FileEngine fileEngine;
 Engine engine;
 DataTransciever dataTransciever;
 GUI gui;

 dataTransciever.connect( &gui, SIGNAL( connectToServer( QHostAddress,quint16 ) ) , SLOT( connectToServer( QHostAddress,quint16 ) ) ) ;

 engine.connect( &gui, SIGNAL( needAllProcessSteps() ) , SLOT( giveProcessSteps() ) ) ;
 engine.connect( &gui, SIGNAL( parseCommand( QString ) ) , SLOT( parseCommand( QString ) ) ) ;

 gui.connect( &engine, SIGNAL( ready() ) , SLOT( start() ) ) ;
 gui.connect( &engine, SIGNAL( addProcessStep( ProcessStep* ) ) , SLOT( addProcessStep( ProcessStep* ) ) ) ;

 fileEngine.connect( &gui, SIGNAL( makeEntry( QString ) ) , SLOT( makeEntry( QString ) ) ) ;
 fileEngine.connect( &gui, SIGNAL( saveLog() ) , SLOT( saveLog() ) ) ;

 gui.connect( &fileEngine, SIGNAL( printToConsole( QString, QString ) ) , SLOT( printToConsole( QString, QString ) ) ) ;
 gui.connect( &engine, SIGNAL( printToConsole( QString, QString ) ) , SLOT( printToConsole( QString, QString ) ) ) ;
 gui.connect( &dataTransciever, SIGNAL( printToConsole( QString, QString ) ) , SLOT( printToConsole( QString, QString ) ) ) ;
 gui.show() ;

 engine.init() ;



 return a.exec() ;
}
