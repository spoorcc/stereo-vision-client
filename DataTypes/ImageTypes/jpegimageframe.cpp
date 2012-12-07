#include "jpegimageframe.h"


JPEGImageFrame::JPEGImageFrame(int numberOfSlices, int streamID, int frameNumber)
{
    _totalNumberOfSlices = numberOfSlices;
    _receivedSlices = 0;

    _streamID = streamID;
    _frameNumber = frameNumber;

   _rawImage.open(QIODevice::ReadWrite);
}

JPEGImageFrame::JPEGImageFrame(const QString& filePath, int streamID, int frameNumber )
{
    QImage image(filePath);

    image.convertToFormat( QImage::Format_RGB888 );
    image.scaled( _defaultWidth, _defaultHeight, Qt::KeepAspectRatio);

    _rawImage.open( QIODevice::ReadWrite);
    image.save( &_rawImage, "JPG");

    _totalNumberOfSlices = 1;
    _receivedSlices = 1;

    _streamID = streamID;
    _frameNumber = frameNumber;
}
JPEGImageFrame::~JPEGImageFrame()
{

}

clientServerProtocol::imageTypes JPEGImageFrame::imageType()
{
    using namespace clientServerProtocol;

    return JPEG;
}

QImage JPEGImageFrame::image()
{
    _rawImage.open(QIODevice::ReadOnly);
    QImage image;
    image.load( &_rawImage, "JPG");
    _rawImage.close();

    return image;
}

bool JPEGImageFrame::needsAllSlicesToBeValid()
{
    return true;
}
