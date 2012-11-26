#include "abstractimageframe.h"

AbstractImageFrame::AbstractImageFrame()
{

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

int AbstractImageFrame::sliceSize()
{
    return _sliceSize;
}

int AbstractImageFrame::streamID()
{
    return _streamID;
}

int AbstractImageFrame::frameNumber()
{
    return _frameNumber;
}

