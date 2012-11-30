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

        emit print( QString("Reading %3 bytes from %1 on port %2").arg( sender.toString() ).arg( senderPort ).arg(datagram->size() ) );
        processDatagram( datagram );
    }
}

void DataReceiveSocket::processDatagram(QByteArray* datagram)
{
    using namespace clientServerProtocol;

    switch( (quint8) datagram->at(0) )
    {

    case SET_PARAMETER:
        processParameter( datagram );
        break;

    case IMAGE_DATA:
        emit imageDataReceived( *datagram );
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
