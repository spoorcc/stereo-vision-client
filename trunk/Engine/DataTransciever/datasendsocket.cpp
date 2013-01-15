#include "datasendsocket.h"

DataSendSocket::DataSendSocket(QObject *parent) :
    QUdpSocket(parent)
{

}
void DataSendSocket::connectToServer( QHostAddress hostAdress, quint16 port )
{
    //Close current connection
    close();

    //Try to connect
    connectToHost( hostAdress, port, QIODevice::WriteOnly );

    //Check if succes
    if( state() )
    {
        emit print("Connected succesfully to" + peerAddress().toString() + " on port " + QString::number( peerPort() ) );
        emit connectionSucces();
    }
    else
    {
        print("Connection failed");
        emit connectionFailed();
    }
}
void DataSendSocket::setParameter(QString processStep, QString parameter, QString value)
{
    using namespace clientServerProtocol;
    QString command = QString( "%1;%2;%3").arg(processStep).arg(parameter).arg(value);

    QByteArray commandInBytes = createDatagram( command );
    int length = commandInBytes.length();
    commandInBytes.prepend( length );

    writeDataToServer( SET_PARAMETER, commandInBytes );
}
void DataSendSocket::sendImage( QImage* image, int streamID )
{
    using namespace clientServerProtocol;

    //Convert image to JPEG in QByteArray
    QByteArray imageData;
    QBuffer imageBuffer(&imageData);
    imageBuffer.open(QIODevice::WriteOnly);
    image->save(&imageBuffer, "JPEG");

    writeDataToServer( IMAGE_DATA, imageData );
}

void DataSendSocket::sendCommand(QString command)
{
    using namespace clientServerProtocol;
    writeDataToServer( UNFORMATTED_COMMAND, command.toAscii() );
}

void DataSendSocket::getImage(clientServerProtocol::imageTypes type, int streamID, bool continous)
{
    qDebug() << type << streamID << continous ;

    QByteArray datagram;    
    datagram.append( (char) type );
    datagram.append( (char) streamID  );

    if( continous )
    {
        datagram.append( clientServerProtocol::getImage::CONTINOUS );
    }
    else
    {
        datagram.append( clientServerProtocol::getImage::SINGLE_SHOT );
    }

    writeDataToServer( clientServerProtocol::GET_IMAGE, datagram );
}

void DataSendSocket::writeDataToServer( clientServerProtocol::clientDataTypes type, QByteArray datagram)
{
    int typeID = type;

    datagram.prepend( typeID );
    datagram.append( "\0" );

    int msgLength = datagram.size();

    quint32 packetCount = qCeil( ((double) msgLength) / MAX_UDP_MESSAGE_SIZE);

    if(packetCount > 1)
    {
        print( QString("Splitting packet into %1 packets").arg(packetCount) );

        //Create a announce message to announce long message
        QByteArray msgLengthPacket;
        msgLengthPacket.append(clientServerProtocol::ANNOUNCE_LONG);
        msgLengthPacket.append(u_int8_t(packetCount));
        msgLengthPacket.append(u_int8_t(packetCount >> 8));
        msgLengthPacket.append(u_int8_t(packetCount >> 16));
        msgLengthPacket.append(u_int8_t(packetCount >> 24));

        //Write the amount of packets first
        write(msgLengthPacket);

        for(int count = 0; count < packetCount; count++)
        {
            waitForBytesWritten(1000);

            int done = write(datagram.mid(count * MAX_UDP_MESSAGE_SIZE, MAX_UDP_MESSAGE_SIZE));

            if(done == -1)
            {
                print( QString("Error sending: Sent %1 packets of %2 to server").arg(count).arg( packetCount ) );
            }
        }
    }
    else
    {
        waitForBytesWritten(1000);
        write(datagram);
    }

    emit bytesWrittenToServer( datagram.size() );
    print( QString("Sent %1 bytes to server").arg( datagram.size() ) );
}

QByteArray DataSendSocket::createDatagram(QString command)
{
    QByteArray datagram = QByteArray( command.toAscii() );

    return datagram;
}
