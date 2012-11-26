#include "mediabuffer.h"

MediaBuffer::MediaBuffer(QObject *parent) :
    QObject(parent)
{
}
void MediaBuffer::addSlice( imageTypes type, quint8 streamID, quint8 frameID, quint16 sliceID, quint16 totalSlices, quint16 sliceLength, QByteArray data   )
{
    foreach( AbstractImageFrame* bufferedImage, _imageBuffer)
    {
        if( bufferedImage->streamID() == streamID )
        {
            if( bufferedImage->frameNumber() == frameID )
            {
                bufferedImage->addSlice( data, sliceID );
            }
            else if( bufferedImage->frameNumber() < frameID || bufferedImage->totalNumberOfSlices() == sliceID-1 )
            {
                //Release the previous frame
                emit frameCompleted( bufferedImage );

                AbstractImageFrame* newFrame = 0;
                //Start a new frame
                switch( type )
                {
                case JPEG:

                    break;
                case RAW:
                    newFrame = new RawImageFrame( totalSlices, sliceLength, streamID, frameID );
                    newFrame->addSlice(data, sliceID);
                    break;
                case DEPTH:

                    break;
                default:

                    break;
                }

                _imageBuffer.push_back( newFrame );
            }
        }
    }
}

