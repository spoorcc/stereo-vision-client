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

    switch( (quint8) datagram->at(0) )
    {

    case SET_PARAMETER:
        processParameter( datagram );
        break;

    case IMAGE_DATA:
        emit imageDataReceived( *datagram );
        break;

    case XML_FULL_CLIENT:
        xmlDataReceived( datagram );
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
    using namespace clientServerProtocol::setParameter;

    int stringLength = ( datagram->at( STRINGLENGTH_MSB ) << 8) + datagram->at( STRINGLENGTH_LSB );

    QString string = QString::fromRawData( (QChar*)datagram->data() + FIRST_DATA_BYTE, stringLength );

    print( QString( "Parameter: " + string) );

    QStringList commandParts = string.split(";");

    if( commandParts.size() == 3 )
    {
        emit parameterReceived( commandParts.at(0), commandParts.at(1), commandParts.at(2) );
    }
    else
    {
        print( QString( "Illegal Parameter received: " + string)  );
    }
}
void DataReceiveSocket::xmlDataReceived( QByteArray* datagram )
{
    QString filePath = QDesktopServices::storageLocation(QDesktopServices::TempLocation);
    QFile* file = new QFile( filePath + "/configXml_stereo-vision-client.xml" );

    file->open( QIODevice::WriteOnly );
    file->write( datagram->mid(1) );
    file->close();

    fullXMLReceived(file);
    print( "XML received" );
}
