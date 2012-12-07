#ifndef ABSTRACTIMAGEFRAME_H
#define ABSTRACTIMAGEFRAME_H

#include "DataTypes/ClientServerProtocol.h"
#include <QByteArray>
#include <QBuffer>
#include <QImage>

class AbstractImageFrame
{
public:
    explicit AbstractImageFrame( );
    virtual ~AbstractImageFrame();

    int totalNumberOfSlices();
    int receivedSlices();
    int missingSlices();

    int streamID();
    int frameNumber();

    virtual clientServerProtocol::imageTypes imageType() = 0;

    bool addSlice(QByteArray slice, int sliceIndex);

    virtual QImage image() = 0;

    void reset( int streamId, int frameNumber, int totalNumberOfSlices );
    void nextFrame( int frameId, int totalNumberOfSlices );
    void changeStream( int streamID);

    void clearBuffer();

    bool complete();
    virtual bool needsAllSlicesToBeValid();

protected:
    int _totalNumberOfSlices;
    int _receivedSlices;
    int _streamID;
    int _frameNumber;

    int _defaultHeight;
    int _defaultWidth;

    QBuffer _rawImage;
};

#endif // ABSTRACTIMAGEFRAME_H
