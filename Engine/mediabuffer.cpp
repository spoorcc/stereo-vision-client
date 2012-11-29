#include "mediabuffer.h"

MediaBuffer::MediaBuffer(QObject *parent) :
    QObject(parent)
{
}

void MediaBuffer::processDatagram(QByteArray *datagram)
{
   int imageType = datagram->at(1);
   int streamID = datagram->at(2);
   int frame = datagram->at(3);
   int sliceIndex = datagram->at(4)<<8 + datagram->at(5);
   int totalSlices = datagram->at(7)<<8 + datagram->at(8);
   int sliceLength = datagram->at(9)<<8 + datagram->at(10);

   addSlice( imageTypes(imageType), streamID, frame, sliceIndex, totalSlices, datagram->right(sliceLength) );
}
void MediaBuffer::setPreviewChannelCount( int i )
{

}

void MediaBuffer::addSlice( imageTypes type, quint8 streamID, quint8 frameID, quint16 sliceID, quint16 totalSlices, QByteArray data )
{
    foreach( AbstractImageFrame* bufferedImage, _imageBuffer)
    {
        if( bufferedImage->streamID() == streamID )
        {
            if( bufferedImage->frameNumber() == frameID )
            {
                bool succes = bufferedImage->addSlice( data, sliceID );
            }
            else if( bufferedImage->frameNumber() < frameID || bufferedImage->totalNumberOfSlices() == sliceID-1 )
            {
                //Release the previous frame
               // emit frameCompleted( bufferedImage );

                AbstractImageFrame* newFrame = 0;

                //Start a new frame
                switch( type )
                {
                case JPEG:

                    break;
                case RAW:
                    newFrame = new RawImageFrame( totalSlices, data.length(), streamID, frameID );
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

