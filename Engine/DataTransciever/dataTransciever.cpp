#include "dataTransciever.h"

/*
  This class contains all methods as commands to control the server.
  These commands are executed by private classes via the communications with the server.
  There are TCP/IP and an UDP nodes that make the physical connection.
  This class will give a signal when new data arrives from the server.
 */

DataTransciever::DataTransciever(QObject *parent) :  QObject(parent)
{
    _udpSendSocket = new QUdpSocket(this);
    _udpReceiveSocket = new QUdpSocket(this);

     //Try to connect to local udp stream
    connect( _udpReceiveSocket, SIGNAL( readyRead() ), this, SLOT( readPendingDatagrams() ));
}

//Connection methods
void DataTransciever::connectToServer( QHostAddress hostAdress, quint16 port )
{
    _udpSendSocket->close();
    _udpReceiveSocket->close();

    QList<QHostAddress > addressList = QNetworkInterface::allAddresses();

    QStringList serverIpAddressParts = hostAdress.toString().split(".");

    foreach( QHostAddress clientAddress, addressList )
    {
        QStringList clientIpAddressParts = clientAddress.toString().split(".");

        if( serverIpAddressParts.at(0) == clientIpAddressParts.at(0) )
        {
            _udpReceiveSocket->bind( clientAddress , port );
            break;
        }
    }

    _udpSendSocket->connectToHost( hostAdress, port, QIODevice::WriteOnly );

    int succes = _udpSendSocket->state();

    print( QString("State: %1").arg( succes ) );
    if(succes)
    {
        print("Connected succesfully to" + _udpSendSocket->peerAddress().toString() + " on port " + QString::number( _udpSendSocket->peerPort() ) );
        emit connectionSucces();
    }
    else
    {
        print("Connection failed");
        emit connectionFailed();
    }
}

//Data commands
void DataTransciever::sendImage( QImage* image )
{
   // QByteArray announceImage = QByteArray("<image>");
   // writeData( announceImage );
    using namespace clientServerProtocol;
    for( int i = 0; i < image->height(); i++ )
    {
        // !!!!-- Probably highly dangerous code --!!!! ////
        QByteArray scanLine = QByteArray( (char*) image->scanLine(i) );
        writeData( IMAGE_DATA, scanLine );
    }

    //QByteArray closeImage = QByteArray("</image>");
   // writeData( closeImage );
}
void DataTransciever::sendCommand( QString command )
{
    using namespace clientServerProtocol;
    writeData( SET_PARAMETER, createDatagram( command) );
}

void DataTransciever::setParameter(QString processStep, QString parameter, QString value)
{
    using namespace clientServerProtocol;
    QString command = QString( "%1;%2;%3").arg(processStep).arg(parameter).arg(value);

    QByteArray commandInBytes = createDatagram( command );
    int length = commandInBytes.length();
    commandInBytes.prepend( length );

    writeData( SET_PARAMETER, commandInBytes );
}

void DataTransciever::getImage(int id, QString processStep, QString streamName, bool continous)
{
    QString message;
    message =  "ID: " + QString::number(id) +" "+ processStep +" "+ streamName +" "+ continous;
    print(message);
}
void DataTransciever::readPendingDatagrams()
{
    print("Reading message");

    while ( _udpReceiveSocket->hasPendingDatagrams() )
    {
        QByteArray* datagram = new QByteArray();
        datagram->resize( _udpReceiveSocket->pendingDatagramSize() );
        QHostAddress sender;
        quint16 senderPort;

        _udpReceiveSocket->readDatagram( datagram->data(), datagram->size(), &sender, &senderPort);

        emit print( QString("Parsing message from %1 on port %2").arg( sender.toString() ).arg( senderPort ) );
        processDatagram( datagram );
    }
}

void DataTransciever::processDatagram(QByteArray* datagram)
{
    using namespace clientServerProtocol;

    switch( QString( datagram->at(0) ).toInt() )
    {

    case SET_PARAMETER:
        processParameter( datagram );
        break;

    case IMAGE_DATA:

        break;

    default:
        QString message = QString( *datagram );
        print( QString( "Unknown Message: " + message) );
        break;
    }

    delete datagram;
}
void DataTransciever::processParameter( QByteArray* datagram )
{
    emit parameterReceived( "test", "test", "test");
}

void DataTransciever::writeData(clientServerProtocol::clientDataTypes type, QByteArray datagram)
{
    int typeID = type;
    datagram.prepend( typeID );
    datagram.append( "\0" );
    _udpSendSocket->write( datagram );
}

QByteArray DataTransciever::createDatagram(QString command)
{
    QByteArray datagram = QByteArray( command.toAscii() );

    return datagram;
}

void DataTransciever::print(QString message)
{
    emit printToConsole("DataTransceiver",message);
}
