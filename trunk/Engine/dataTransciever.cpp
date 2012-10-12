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
    QByteArray announceImage = QByteArray("<image>");
    writeData( announceImage );

    for( int i = 0; i < image.height(); i++ )
    {
        // !!!!-- Probably highly dangerous code --!!!! ////
        QByteArray scanLine = QByteArray( (char*) image.scanLine(i) );
        writeData( scanLine );
    }

    QByteArray closeImage = QByteArray("</image>");
    writeData( closeImage );
}
void DataTransciever::sendCommand( QString processtep, QString parameter, QString value )
{
    writeData( createDatagram( processtep, parameter, value) );
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
    //FIXME: Just for debugging
    //Get data from the datagram
    print( QString::number( datagram.toInt() ));


}

void DataTransciever::writeData(QByteArray datagram)
{
    _udpSocket->write( datagram );
}


QByteArray DataTransciever::createDatagram(QString processStep, QString parameter, QString value)
{
    QString message = QString( processStep + " " + parameter + " " + value );
    QByteArray datagram = QByteArray( message.toAscii() );

    return datagram;
}

void DataTransciever::print(QString message)
{
    emit printToConsole("DataTransceiver",message);
}
