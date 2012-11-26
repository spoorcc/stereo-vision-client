#ifndef RAWIMAGEFRAME_H
#define RAWIMAGEFRAME_H

#include <QByteArray>
#include "abstractimageframe.h"

class RawImageFrame : public AbstractImageFrame
{
public:
    RawImageFrame(int totalNumberOfSlices, int sliceSize, int streamID, int frameNumber );
    RawImageFrame(QString filePath );
    ~RawImageFrame();

    virtual bool addSlice(QByteArray slice, int sliceIndex);
    virtual imageTypes imageType();

private:
    QByteArray _rawImage;
};

#endif // RAWIMAGEFRAME_H
