#include "mediabuffer.h"

MediaBuffer::MediaBuffer(QObject *parent) :
    QObject(parent)
{
    initImageBuffers();
}

void MediaBuffer::initImageBuffers()
{
    QString defaultImage = ":/Icons/Icon";

    int numberOfChannels = HORCHANNELCOUNT * VERCHANNELCOUNT;

    for( int i = 0; i < numberOfChannels; i++ )
    {                 
         AbstractImageFrame* bufferedImage = new JPEGImageFrame( defaultImage );
        _imageBuffer.push_front( bufferedImage );
    }

    emit print( "Mediabuffer initialised");
}

void MediaBuffer::processImageDatagram(QByteArray datagram)
{
   using namespace clientServerProtocol::imageData;

   int imageType = datagram.at(IMAGETYPE);
   int streamID = datagram.at(STREAMID);
   int frame = datagram.at(FRAMEID);

   int sliceIndex  = datagram.at(SLICEINDEX_MSB)  << sizeof(char) + datagram.at( SLICEINDEX_LSB );
   int totalSlices = datagram.at(TOTALSLICES_MSB) << sizeof(char) + datagram.at( TOTALSLICES_LSB );
   int sliceLength = datagram.at(SLICELENGTH_MSB) << sizeof(char) + datagram.at( SLICELENGTH_LSB );

   //addSlice( clientServerProtocol::imageTypes(imageType), streamID, frame, sliceIndex, totalSlices, datagram.right(sliceLength) );
   addFrame( clientServerProtocol::imageTypes(imageType), streamID, frame, datagram.right(sliceLength) );
}

void MediaBuffer::subscribeChannelToStream(int channelID, int streamID)
{
    QImage image = _imageBuffer.at(channelID)->image();

    emit imageReceived( image, channelID);

    _imageBuffer.at(channelID)->changeStream( streamID );
}

void MediaBuffer::flushBuffers()
{
    for( int i = 0; i < _imageBuffer.size(); i++)
    {
        emit imageReceived( _imageBuffer.at(i)->image(), i);
    }
}

void MediaBuffer::resetBuffer( int channelID )
{
    _imageBuffer.at( channelID );
}

void MediaBuffer::addSlice( clientServerProtocol::imageTypes type, quint8 streamId, quint8 frameID, quint16 sliceID, quint16 totalSlices, QByteArray data )
{
    using namespace clientServerProtocol;

    int bufferSize = _imageBuffer.size();
    for( int i = 0; i < bufferSize; i++)
    {
        AbstractImageFrame* bufferedImage = _imageBuffer.at(i);

        // If the stream matches the stream of that previewchannel
        if( bufferedImage->streamID() == streamId )
        {
            if( bufferedImage->frameNumber() != frameID )
            {
                if( !bufferedImage->needsAllSlicesToBeValid() )
                {
                    emit imageReceived( bufferedImage->image(), i );
                }

                bufferedImage->nextFrame( frameID, totalSlices);
                bufferedImage->addSlice( data, sliceID );
            }
            else
            {
                if( sliceID > bufferedImage->receivedSlices() )
                {
                    if( bufferedImage->needsAllSlicesToBeValid() )
                    {
                        // Image is corrupted
                    }
                    else
                    {
                        bool complete = bufferedImage->addSlice( data, sliceID );
                    }
                }
            }
        }
        else if( i >= (bufferSize + 1) )
        {
            emit print( QString("Stream %1 not selected in any channel").arg( streamId));
        }
    }

}

void MediaBuffer::addFrame(clientServerProtocol::imageTypes type, quint8 streamId, quint8 frameID, QByteArray data)
{
    using namespace clientServerProtocol;

    int bufferSize = _imageBuffer.size();
    for( int i = 0; i < bufferSize; i++)
    {
        AbstractImageFrame* bufferedImage = _imageBuffer.at(i);

        // If the stream matches the stream of that previewchannel
        if( bufferedImage->streamID() == streamId )
        {
            if( bufferedImage->frameNumber() != frameID )
            {
                bufferedImage->nextFrame(data, frameID);
                emit imageReceived( bufferedImage->image(), i );
            }
            else
            {
               bufferedImage->nextFrame(data, frameID);
               emit imageReceived( bufferedImage->image(), i );
            }
        }
        else if( i >= (bufferSize + 1) )
        {
            emit print( QString("Stream %1 not selected in any channel").arg( streamId));
        }
    }
}

