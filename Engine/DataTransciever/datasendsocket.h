#ifndef DATASENDSOCKET_H
#define DATASENDSOCKET_H

#include <QUdpSocket>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QDebug>
#include <qmath.h>

#include "DataTypes/ClientServerProtocol.h"

class DataSendSocket : public QUdpSocket
{
    Q_OBJECT
public:
    explicit DataSendSocket(QObject *parent = 0);
    
    void connectToServer(QHostAddress hostAdress, quint16 port);
    void setParameter(QString processStep, QString parameter, QString value);

signals:
    void print( QString message );
    void connectionSucces();
    void connectionFailed();
    void bytesWrittenToServer( int bytes );

public slots:
    void sendImage( QImage* image, int streamID);
    void sendCommand( QString command );

    void getImage( clientServerProtocol::imageTypes type, int streamID, bool continous);
    
private:
    void writeDataToServer( clientServerProtocol::clientDataTypes type, QByteArray datagram);

    QByteArray createDatagram(QString command);

};

#endif // DATASENDSOCKET_H
