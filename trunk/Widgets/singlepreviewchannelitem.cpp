#include "singlepreviewchannelitem.h"


SinglePreviewChannelItem::SinglePreviewChannelItem()
{
    _channelNumber = 0;
    _size = QRect(0,0, PREVIEWCHANNELWIDTH,PREVIEWCHANNELHEIGTH);
    _mode = config;
}

QRectF SinglePreviewChannelItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0 - penWidth/2, 0-penWidth/2, PREVIEWCHANNELWIDTH + penWidth, PREVIEWCHANNELHEIGTH + penWidth);
}

void SinglePreviewChannelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(_size);

    QRect textPos = QRect( PREVIEWCHANNELWIDTH/2, PREVIEWCHANNELHEIGTH/2, _size.width(), _size.height());

    switch( _mode ){

    case config:
        painter->drawText( textPos, QString::number( _channelNumber ) + " config" );

        break;
    case preview:
        painter->drawText( textPos, QString::number( _channelNumber ) + " Preview" );
        break;
    case replace:
        painter->drawText( textPos, QString::number( _channelNumber ) + " Replace" );
        break;
    }

}
void SinglePreviewChannelItem::setChannelNumber( int number)
{
    if( number >= 0)
    {
        _channelNumber = number;
    }
}

int SinglePreviewChannelItem::channelNumber()
{
    return _channelNumber;
}
void SinglePreviewChannelItem::setMode( SinglePreviewChannelItem::Mode mode)
{
    _mode = mode;
}
