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
    
    void addSlice(imageTypes type, quint8 streamID, quint8 frameID, quint16 sliceID, quint16 totalSlices, quint16 sliceLength, QByteArray data);
signals:

    void frameCompleted( AbstractImageFrame* frame);
public slots:

private:
    std::deque< AbstractImageFrame* > _imageBuffer;

};

#endif // MEDIABUFFER_H
