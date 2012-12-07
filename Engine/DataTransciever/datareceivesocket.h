#ifndef DATARECEIVESOCKET_H
#define DATARECEIVESOCKET_H

#include <QUdpSocket>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QtNetwork>

#include <QByteArray>
#include <QByteRef>

#include "DataTypes/ClientServerProtocol.h"

class DataReceiveSocket : public QUdpSocket
{
    Q_OBJECT
public:
    explicit DataReceiveSocket(QObject *parent = 0);
    
    void connectToServer(QHostAddress hostAdress, quint16 port);

signals:
    void print( QString message );

    void parameterReceived( QString processStep, QString parameter, QString value);

    void imageDataReceived( QByteArray data );
    void bytesReceived( int bytes);

public slots:


private slots:
    void readPendingDatagrams();

private:
    void processDatagram(QByteArray *datagram);
    void processParameter(QByteArray *datagram);
    
};

#endif // DATARECEIVESOCKET_H
