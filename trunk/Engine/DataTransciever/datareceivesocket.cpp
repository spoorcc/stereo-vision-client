#include "datareceivesocket.h"

DataReceiveSocket::DataReceiveSocket(QObject *parent) :
    QUdpSocket(parent)
{
    connect( this, SIGNAL( readyRead() ), this, SLOT( readPendingDatagrams() ));
}
void DataReceiveSocket::connectToServer( QHostAddress hostAdress, quint16 port )
{
    this->close();

    QList<QHostAddress > addressList = QNetworkInterface::allAddresses();
    QStringList serverIpAddressParts = hostAdress.toString().split(".");

    foreach( QHostAddress clientAddress, addressList )
    {
        QStringList clientIpAddressParts = clientAddress.toString().split(".");

        if( serverIpAddressParts.at(0) == clientIpAddressParts.at(0) )
        {
            this->bind( clientAddress , port );
            break;
        }
    }
}
void DataReceiveSocket::readPendingDatagrams()
{
    while ( hasPendingDatagrams() )
    {
        QByteArray* datagram = new QByteArray();
        datagram->resize( pendingDatagramSize() );
        QHostAddress sender;
        quint16 senderPort;

        readDatagram( datagram->data(), datagram->size(), &sender, &senderPort);

        emit print( QString("Received: %1").arg(datagram->data()) );

        // If a long message is announced
        if( (quint8) datagram->at(0) == clientServerProtocol::ANNOUNCE_LONG )
        {
            //Get the number of messages
            quint32 messagesPending;
            QByteArray count = datagram->mid(1,4);
            memcpy( &messagesPending, count, sizeof(quint32) );

            emit print( QString("Long message - consists of %1 message(s)").arg(messagesPending) );

            datagram->clear();
            datagram->reserve( 512 * messagesPending );

            QByteArray* partialDatagram = new QByteArray();

            QTime timer;

            while( messagesPending > 0 )
            {
                timer.start();
                while( !hasPendingDatagrams() )
                {
                    //time-out after 1000 msec
                    if( timer.elapsed() > 1000)
                    {
                        emit print( QString("Incomplete message - missing %1 message(s)").arg(messagesPending) );
                        return;
                    }
                }

                partialDatagram->clear();
                partialDatagram->resize( pendingDatagramSize() );

                readDatagram( partialDatagram->data(), partialDatagram->size(), &sender, &senderPort);
                datagram->push_back( *partialDatagram );

                messagesPending--;
            }
        }

        emit bytesReceived( datagram->size() );
        emit print( QString("Reading %3 bytes from %1 on port %2").arg( sender.toString() ).arg( senderPort ).arg(datagram->size() ) );
        processDatagram( datagram );
    }
}

void DataReceiveSocket::processDatagram(QByteArray* datagram)
{
    using namespace clientServerProtocol;

    emit print( QString("This should be a P %1 seen as a %2").arg( datagram->at(0) ).arg(QString::number((quint8) datagram->at(0))));

    switch( (quint8) datagram->at(0) )
    {

    case SET_PARAMETER:
        processParameter( datagram );
        break;

    case IMAGE_DATA:
        emit imageDataReceived( *datagram );
        emit print("Image");
        break;

    default:
        QString message = QString( *datagram );
        print( QString( "Unknown Message: " + message) );
        break;
    }

    delete datagram;
}
void DataReceiveSocket::processParameter( QByteArray* datagram )
{
    emit parameterReceived( "test", "test", "test");
}
