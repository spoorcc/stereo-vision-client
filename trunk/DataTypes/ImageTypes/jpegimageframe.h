#ifndef JPEGIMAGEFRAME_H
#define JPEGIMAGEFRAME_H

#include "abstractimageframe.h"

class JPEGImageFrame : public AbstractImageFrame
{
public:
    JPEGImageFrame(int numberOfSlices, int streamID, int frameNumber);
    JPEGImageFrame(const QString &filePath, int streamID = 0 , int frameNumber=0);
    JPEGImageFrame( QByteArray imageData, int streamID = 0, int frameNumber = 0);
    ~JPEGImageFrame();

    virtual clientServerProtocol::imageTypes imageType();
    virtual QImage image();
    virtual bool needsAllSlicesToBeValid();
};

#endif // JPEGIMAGEFRAME_H
