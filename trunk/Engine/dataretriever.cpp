#include "dataretriever.h"

/*
  This class contains all methods as commands to control the server.
  These commands are executed by private classes via the communications with the server.
  There are TCP/IP and an UDP nodes that make the physical connection.
  This class will give a signal when new data arrives from the server.
 */

DataRetriever::DataRetriever(QObject *parent) :
    QObject(parent)
{

}

//Connection methods
void DataRetriever::connectToServer( void )
{

}

//Data commands
void DataRetriever::sendImage( QImage image )
{

}
