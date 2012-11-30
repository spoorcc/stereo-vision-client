#include "mediabuffer.h"

MediaBuffer::MediaBuffer(QObject *parent) :
    QObject(parent)
{
    initImageBuffers();
}

void MediaBuffer::initImageBuffers()
{

    int numberOfChannels = HORCHANNELCOUNT * VERCHANNELCOUNT;

    for( int i = 0; i < numberOfChannels; i++ )
    {
        AbstractImageFrame* bufferedImage = 0;
        _imageBuffer.push_front( bufferedImage );

        _subscriptions << -1;
    }
}

void MediaBuffer::processImageDatagram(QByteArray *datagram)
{
   using namespace clientServerProtocol::imageData;

   int imageType = datagram->at(IMAGETYPE);
   int streamID = datagram->at(STREAMID);
   int frame = datagram->at(FRAMEID);

   int sliceIndex  = datagram->at(SLICEINDEX_MSB)  << 8 + datagram->at( SLICEINDEX_LSB );
   int totalSlices = datagram->at(TOTALSLICES_MSB) << 8 + datagram->at( TOTALSLICES_LSB );
   int sliceLength = datagram->at(SLICELENGTH_MSB) << 8 + datagram->at( SLICELENGTH_LSB );

   addSlice( clientServerProtocol::imageTypes(imageType), streamID, frame, sliceIndex, totalSlices, datagram->right(sliceLength) );
}

void MediaBuffer::subscribeChannelToStream(int channelID, QString streamID)
{


    _imageBuffer.at( channelID );
}

void MediaBuffer::resetBuffer( int channelID )
{
    _imageBuffer.at( channelID );
}

void MediaBuffer::addSlice( clientServerProtocol::imageTypes type, quint8 streamID, quint8 frameID, quint16 sliceID, quint16 totalSlices, QByteArray data )
{
    using namespace clientServerProtocol;

    foreach( AbstractImageFrame* bufferedImage, _imageBuffer)
    {
        if( bufferedImage->streamID() == streamID )
        {
            if( bufferedImage->frameNumber() == frameID )
            {
                bool succes = bufferedImage->addSlice( data, sliceID );
            }
            else if( bufferedImage->frameNumber() < frameID  )
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
                return;
            }
        }
        else
        {
            //Add new stream to buffer (if neccessary)
        }

    }
}

