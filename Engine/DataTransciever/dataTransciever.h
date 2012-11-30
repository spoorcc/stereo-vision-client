#ifndef DATATRANSCIEVER_H
#define DATATRANSCIEVER_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The dataTransciever setups the connection with the server and keeps listening in a seperate thread for incoming messages.

*/



// Global includes
#include <QObject>
#include <QImage>

#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QtNetwork>

#include <QByteArray>
#include <QByteRef>

#include "DataTypes/ClientServerProtocol.h"

#include "Engine/mediabuffer.h"

class DataTransciever : public QObject
{
    Q_OBJECT
public:
    explicit DataTransciever(QObject *parent = 0);

signals:
    void printToConsole( QString sender, QString message );
    void connectionSucces();
    void connectionFailed();

    void parameterReceived( QString processStep, QString parameter, QString value);
    void imageSliceReceived( clientServerProtocol::imageTypes type, quint8 streamID, quint8 frameID, quint16 sliceID, quint16 totalSlices, quint16 sliceLength, QByteArray data   );
    
public slots:

    //Connection methods
    void connectToServer( QHostAddress hostAdress, quint16 port = 7755 );
    void readPendingDatagrams(); //Ugly code, it exposes this public method to the world

    //Send methods
    void sendImage( QImage *image );
    void sendCommand( QString command );
    void setParameter( QString processStep, QString parameter, QString value);

    void getImage( int id, QString processStep, QString streamName, bool continous);

private:
    QUdpSocket* _udpSendSocket;
    QUdpSocket* _udpReceiveSocket;

    void processDatagram( QByteArray *datagram );
    void processParameter(QByteArray *datagram);
    void writeData( clientServerProtocol::clientDataTypes type, QByteArray datagram );

    QByteArray createDatagram( QString command );

    void print( QString message );
};

#endif // DATATRANSCIEVER_H
