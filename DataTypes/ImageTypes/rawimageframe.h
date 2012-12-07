#ifndef RAWIMAGEFRAME_H
#define RAWIMAGEFRAME_H

#include <QByteArray>
#include "abstractimageframe.h"
#include <cmath>

class RawImageFrame : public AbstractImageFrame
{
public:
    RawImageFrame(int totalNumberOfSlices, int streamID, int frameNumber );
    RawImageFrame(const QString &filePath, int streamID=0 , int frameNumber=0 );
    ~RawImageFrame();

    virtual clientServerProtocol::imageTypes imageType();

    virtual QImage image();

    virtual bool needsAllSlicesToBeValid();

private:




};

#endif // RAWIMAGEFRAME_H
