#include "abstractimageframe.h"

AbstractImageFrame::AbstractImageFrame()
{
    _defaultWidth = 800;
    _defaultHeight = 600;
}

AbstractImageFrame::~AbstractImageFrame()
{
}

int AbstractImageFrame::totalNumberOfSlices()
{
    return _totalNumberOfSlices;
}

int AbstractImageFrame::receivedSlices()
{
    return _receivedSlices;
}

int AbstractImageFrame::missingSlices()
{
    return _totalNumberOfSlices - _receivedSlices;
}


int AbstractImageFrame::streamID()
{
    return _streamID;
}

int AbstractImageFrame::frameNumber()
{
    return _frameNumber;
}
bool AbstractImageFrame::complete()
{
    return (_totalNumberOfSlices == _receivedSlices);
}

bool AbstractImageFrame::needsAllSlicesToBeValid()
{
    return true;
}
bool AbstractImageFrame::addSlice( QByteArray slice, int sliceIndex )
{
    _rawImage.write( slice );

    _receivedSlices++;

    if( _receivedSlices >= _totalNumberOfSlices )
    {
        _rawImage.close();
    }

    return true;
}

void AbstractImageFrame::reset(int streamId, int frameNumber, int totalNumberOfSlices)
{
    _streamID = streamId;

    nextFrame( frameNumber, totalNumberOfSlices);
}

void AbstractImageFrame::nextFrame(int frameId, int totalNumberOfSlices)
{
    _rawImage.open(QIODevice::ReadWrite);

    _receivedSlices = 0;
    _frameNumber = frameId;
    _totalNumberOfSlices = totalNumberOfSlices;
}
void AbstractImageFrame::nextFrame(QByteArray imageData, int frameId)
{
    _rawImage.setData( imageData );

    _frameNumber = frameId;

    _totalNumberOfSlices = 1;
    _receivedSlices = 1;
}
void AbstractImageFrame::changeStream(int streamID)
{
    _rawImage.close();

    _streamID = streamID;
}

void AbstractImageFrame::clearBuffer()
{
    _rawImage.open(QIODevice::ReadWrite);
    _rawImage.buffer().clear();

    _receivedSlices = 0;
    _totalNumberOfSlices = -1;

}
