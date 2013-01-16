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
#include "Engine/DataTransciever/dataTransciever.h"
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

 GUI gui;

 engine.connect( &gui, SIGNAL( connectToServer( QHostAddress,quint16 ) ) , SIGNAL( connectToServer( QHostAddress,quint16 ) ) ) ;

 gui.connect( &engine, SIGNAL(imageReceived(QImage,int)),SIGNAL(imageForPreviewWindow(QImage, int)));

 engine.connect( &gui, SIGNAL(subscribeToStream( int, QString, QString, bool)), SLOT( subscribePreviewChannelToStream(int, QString, QString,  bool)));

 engine.connect( &gui, SIGNAL( needAllProcessSteps() ) , SLOT( giveProcessSteps() ) ) ;
 engine.connect( &gui,SIGNAL( commandForServer(QString)), SIGNAL(commandForServer(QString)));
 engine.connect( &gui, SIGNAL(replaceStreamRequest(QString,QString,QImage*)), SLOT( replaceStream(QString, QString, QImage*) ) );
 engine.connect( &gui, SIGNAL(setValueOnServer(QString,QString,QString)), SIGNAL(setValueOnServer(QString,QString,QString)));
 engine.connect( &gui, SIGNAL( requestXML() ), SIGNAL( requestXML() ));
 engine.connect( &gui, SIGNAL(flushImageBuffers()), SLOT(flushImageBuffers()));

 gui.connect( &engine, SIGNAL( ready() ) , SLOT( start() ) ) ;
 gui.connect( &engine, SIGNAL( addProcessStep( ProcessStep* ) ) , SLOT( addProcessStep( ProcessStep* ) ) ) ;
 gui.connect( &engine, SIGNAL( clearGui() ), SLOT(clearGui() ));

 fileEngine.connect( &gui, SIGNAL( makeEntry( QString ) ) , SLOT( makeEntry( QString ) ) ) ;
 fileEngine.connect( &gui, SIGNAL( saveLog() ) , SLOT( saveLog() ) ) ;
 fileEngine.connect( &gui, SIGNAL( setTargetDirectory(QString)), SLOT( setDestination(QString) ));

 gui.connect( &fileEngine, SIGNAL( printToConsole( QString, QString ) ) , SLOT( printToConsole( QString, QString ) ) ) ;
 gui.connect( &engine, SIGNAL( printToConsole( QString, QString ) ) , SLOT( printToConsole( QString, QString ) ) ) ;
 gui.show() ;

 engine.init() ;

 return a.exec() ;
}
