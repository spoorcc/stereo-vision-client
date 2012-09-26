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
    _udpSocket = new QUdpSocket( this );
    _udpSocket.bind( QHostAddress::LocalHost, 7755);

    connect( udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

//Connection methods
void DataRetriever::connectToServer( void )
{

}

//Data commands
void DataRetriever::sendImage( QImage image )
{

}

void DataRetriever::readPendingDatagrams()
{
    while (_udpSocket.hasPendingDatagrams() )
    {
        QByteArray datagram;
        datagram.resize( _udpSocket.pendingDatagramSize() );
        QHostAddress sender;
        quint16 senderPort;

        _udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        processDatagram( datagram );
    }
}

void DataRetriever::processDatagram(QByteArray datagram)
{
    //Get data from the datagram


}
