#include "dataTransciever.h"

/*
  This class contains all methods as commands to control the server.
  These commands are executed by private classes via the communications with the server.
  There are TCP/IP and an UDP nodes that make the physical connection.
  This class will give a signal when new data arrives from the server.
 */

DataTransciever::DataTransciever(QObject *parent) :  QObject(parent)
{
    _sendSocket = new DataSendSocket(this);
    _receiveSocket = new DataReceiveSocket(this);

    connect( _sendSocket,    SIGNAL(print(QString)), SLOT(print(QString) ) );
    connect( _receiveSocket, SIGNAL(print(QString)), SLOT(print(QString) ) );

    connect( _receiveSocket, SIGNAL(imageDataReceived(QByteArray)), SIGNAL(imageDataReceived(QByteArray)));
}

//Connection methods
void DataTransciever::connectToServer( QHostAddress hostAdress, quint16 port )
{
    _sendSocket->connectToServer(hostAdress,port);
    _receiveSocket->connectToServer(hostAdress,port);
}

//Data commands
void DataTransciever::sendCommand( QString command )
{
    _sendSocket->sendCommand( command );
}

void DataTransciever::setParameter(QString processStep, QString parameter, QString value)
{
    _sendSocket->setParameter( processStep, parameter, value);
}
void DataTransciever::getImage( int streamID, bool continous )
{
     clientServerProtocol::imageTypes type = clientServerProtocol::JPEG;

    _sendSocket->getImage( type, streamID, continous );
}

void DataTransciever::print(QString message)
{
    emit printToConsole("DataTransceiver",message);
}

