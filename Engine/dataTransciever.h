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

    //Send methods
    void sendImage( QImage image );
    void sendCommand( int command );

private:
    QUdpSocket* _udpSocket;

    void readPendingDatagrams();
    void processDatagram( QByteArray datagram );

    void print( QString message );
};

#endif // DATATRANSCIEVER_H
