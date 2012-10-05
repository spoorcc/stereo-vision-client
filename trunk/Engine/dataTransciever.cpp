#include "dataTransciever.h"

/*
  This class contains all methods as commands to control the server.
  These commands are executed by private classes via the communications with the server.
  There are TCP/IP and an UDP nodes that make the physical connection.
  This class will give a signal when new data arrives from the server.
 */

DataTransciever::DataTransciever(QObject *parent) :  QObject(parent)
{
    _udpSocket = new QUdpSocket(this);

    //Try to connect to local udp stream
    connectToServer( QHostAddress::LocalHost);
    connect( _udpSocket, SIGNAL( readyRead() ), this, SLOT( readPendingDatagrams() ));
}

//Connection methods
void DataTransciever::connectToServer( QHostAddress hostAdress, quint16 port )
{
    bool succes = _udpSocket->bind( hostAdress, port );

    if(succes)
    {
        print("Connected succesfully to" + hostAdress.toString() + " on port " + QString::number(port) );
        emit connectionSucces();
    }
    else
    {
        print("Connection failed");
        emit connectionFailed();
    }
}

//Data commands
void DataTransciever::sendImage( QImage image )
{

}
void DataTransciever::sendCommand( int command )
{

}
void DataTransciever::readPendingDatagrams()
{
    while (_udpSocket->hasPendingDatagrams() )
    {
        QByteArray datagram;
        datagram.resize( _udpSocket->pendingDatagramSize() );
        QHostAddress sender;
        quint16 senderPort;

        _udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        processDatagram( datagram );
    }
}

void DataTransciever::processDatagram(QByteArray datagram)
{
    //Get data from the datagram


}

void DataTransciever::print(QString message)
{
    emit printToConsole("DataTransceiver",message);
}
