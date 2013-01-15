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

   addFrame( clientServerProtocol::imageTypes(imageType), streamID, frame, datagram.mid(FRAMEID+1) );

}

void MediaBuffer::subscribeChannelToStream(int channelID, int streamID)
{
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
    //Huh?
    _imageBuffer.at( channelID );
}

void MediaBuffer::addFrame(clientServerProtocol::imageTypes type, quint8 streamId, quint8 frameID, QByteArray data)
{
    using namespace clientServerProtocol;

    emit print( QString("Image in buffer - addFrame type %1 stream %2 frame %3 size %4").arg(type).arg(streamId).arg(frameID).arg( data.size() ) );

    int bufferSize = _imageBuffer.size();

    for( int i = 0; i < bufferSize; i++)
    {
        AbstractImageFrame* bufferedImage = _imageBuffer.at(i);

        // If the stream matches the stream of that previewchannel
        if( bufferedImage->streamID() == streamId )
        {
            emit print( QString("Stream %1 matches received streamID").arg(i));

            QImage image = QImage::fromData(data);

            image.scaled(800,600,Qt::KeepAspectRatio);

            bufferedImage->nextFrame(data, frameID);
            emit imageReceived( image, i );

        }
        else if( i >= (bufferSize + 1) )
        {
            emit print( QString("Stream %1 not selected in any channel").arg( streamId));
        }
    }
}

