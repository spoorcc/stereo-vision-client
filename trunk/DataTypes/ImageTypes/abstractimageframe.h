#ifndef ABSTRACTIMAGEFRAME_H
#define ABSTRACTIMAGEFRAME_H

#include "DataTypes/ClientServerProtocol.h"
#include <QByteArray>
#include <QImage>

class AbstractImageFrame
{
public:
    explicit AbstractImageFrame( );
    virtual ~AbstractImageFrame();

    int totalNumberOfSlices();
    int receivedSlices();
    int missingSlices();

    int sliceSize();

    int streamID();
    int frameNumber();

    virtual imageTypes imageType() = 0;

    virtual bool addSlice(QByteArray slice, int sliceIndex) = 0;

protected:
    int _totalNumberOfSlices;
    int _receivedSlices;
    int _sliceSize;
    int _streamID;
    int _frameNumber;
};

#endif // ABSTRACTIMAGEFRAME_H
