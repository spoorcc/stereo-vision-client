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
    void sendCommand( QString processtep, QString parameter, QString value );

private:
    QUdpSocket* _udpSocket;

    void processDatagram( QByteArray datagram );
    void writeData( QByteArray datagram );

    QByteArray createDatagram( QString processStep, QString parameter, QString value);

    void print( QString message );
};

#endif // DATATRANSCIEVER_H
