#ifndef DATATRANSCIEVER_H
#define DATATRANSCIEVER_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The dataTransciever setups the connection with the server and keeps listening in a seperate thread for incoming messages.

*/

#define DATAGRAMSIZE 512

// Global includes
#include <QObject>
#include <QImage>

#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QtNetwork>

enum MessageType{ COMMAND = 0x01, RAW_IMAGE = 0x02 };

class DataTransciever : public QObject
{
    Q_OBJECT
public:
    explicit DataTransciever(QObject *parent = 0);

signals:
    void printToConsole( QString sender, QString message );
    void connectionSucces();
    void connectionFailed();
    
public slots:
    //Connection methods
    void connectToServer( QHostAddress hostAdress, quint16 port = 7755 );
    void readPendingDatagrams(); //Ugly code, it exposes this public method to the world

    //Send methods
    void sendImage( QImage image );
    void sendCommand( QString command );

private:
    QUdpSocket* _udpSendSocket;
    QUdpSocket* _udpReceiveSocket;

    void processDatagram( QByteArray datagram );
    void writeData( QByteArray datagram, MessageType type );

    QByteArray createDatagram( QString command );

    void print( QString message );
};

#endif // DATATRANSCIEVER_H
