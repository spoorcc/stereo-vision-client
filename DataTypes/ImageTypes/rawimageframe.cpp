#include "rawimageframe.h"

RawImageFrame::RawImageFrame(int numberOfSlices, int sliceSize, int streamID, int frameNumber)
{
    _totalNumberOfSlices = numberOfSlices;
    _receivedSlices = 0;

    _sliceSize = sliceSize;
    _streamID = streamID;
    _frameNumber = frameNumber;

    _rawImage = QByteArray( _totalNumberOfSlices * _sliceSize, (char) 0 );
}
RawImageFrame::RawImageFrame(QString filePath)
{

}
RawImageFrame::~RawImageFrame()
{
    _rawImage.clear();
}
bool RawImageFrame::addSlice( QByteArray slice, int sliceIndex )
{     
    //If the slice is of the expected size or smaller, add it to the buffer
    if( _sliceSize >= slice.size() )
    {
        _rawImage.replace( sliceIndex, slice);
        _receivedSlices++;
        return true;
    }
    else
    {
        return false;
    }
}

imageTypes RawImageFrame::imageType()
{
    return RAW;
}
