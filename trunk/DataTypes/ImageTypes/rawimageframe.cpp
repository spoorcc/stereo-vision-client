#include "rawimageframe.h"

RawImageFrame::RawImageFrame(int numberOfSlices, int streamID, int frameNumber)
{
    _totalNumberOfSlices = numberOfSlices;
    _receivedSlices = 0;

    _streamID = streamID;
    _frameNumber = frameNumber;

   _rawImage.open(QIODevice::ReadWrite);
}

RawImageFrame::RawImageFrame(const QString& filePath, int streamID, int frameNumber )
{
    //Construct a image with the proper contraints
    QImage image(filePath);
    image.convertToFormat( QImage::Format_RGB888 );
    image.scaled( _defaultWidth, _defaultHeight, Qt::KeepAspectRatio);

    //Write the raw data into a buffer
    _rawImage.open( QIODevice::ReadWrite);
    image.save( &_rawImage, "BMP");

    //Make sure the image acts like a completed image
    _totalNumberOfSlices = 1;
    _receivedSlices = 1;

    //Set the given values
    _streamID = streamID;
    _frameNumber = frameNumber;
}

RawImageFrame::RawImageFrame(QByteArray imageData, int streamID, int frameNumber)
{
    _rawImage.open( QIODevice::WriteOnly );
    _rawImage.write( imageData );
    _rawImage.close();

    _streamID = streamID;
    _frameNumber = frameNumber;

    _totalNumberOfSlices = 1;
    _receivedSlices = 1;
}
RawImageFrame::~RawImageFrame()
{

}

clientServerProtocol::imageTypes RawImageFrame::imageType()
{
    using namespace clientServerProtocol;

    return RAW;
}

QImage RawImageFrame::image()
{    
    _rawImage.open(QIODevice::ReadOnly);
    QImage image;
    image.load( &_rawImage, "BMP");
    _rawImage.close();

    return image;
}

bool RawImageFrame::needsAllSlicesToBeValid()
{
    return false;
}
