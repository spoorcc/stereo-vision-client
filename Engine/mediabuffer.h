#ifndef MEDIABUFFER_H
#define MEDIABUFFER_H

// Global includes
#include <QObject>
#include <QImage>
#include <deque>

// Local includes
#include "DataTypes/ClientServerProtocol.h"
#include "DataTypes/ImageTypes/allimagetypes.h"

class MediaBuffer : public QObject
{
    Q_OBJECT
public:
    explicit MediaBuffer(QObject *parent = 0);
    
    void processDatagram( QByteArray* datagram );

    void setPreviewChannelCount(int i);

signals:
    void imageReceived( QImage image, int channel);

public slots:

private:
    std::deque< AbstractImageFrame* > _imageBuffer;

    std::vector< QImage* > _receiveBuffers;
    std::vector< QImage* > _sendBuffers;

    void addSlice(imageTypes type, quint8 streamID, quint8 frameID, quint16 sliceID, quint16 totalSlices, QByteArray data);
};

#endif // MEDIABUFFER_H
