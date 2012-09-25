#ifndef DATARETRIEVER_H
#define DATARETRIEVER_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The dataretriever setups the connection with the server and keeps listening ina seperate thread for incoming messages.

*/

// Global includes
#include <QObject>
#include <QImage>

class DataRetriever : public QObject
{
    Q_OBJECT
public:
    explicit DataRetriever(QObject *parent = 0);
    
signals:
    void print( QString message );
    
public slots:
    void connectToServer( void );
    void sendImage( QImage image );

    
};

#endif // DATARETRIEVER_H
