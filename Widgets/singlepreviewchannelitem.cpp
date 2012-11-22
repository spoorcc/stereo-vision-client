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
    QRectF boundingRect = QRectF(0 - penWidth/2, 0-penWidth/2, PREVIEWCHANNELWIDTH + penWidth, PREVIEWCHANNELHEIGTH + penWidth);
    return boundingRect;
}

void SinglePreviewChannelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(_size);

    QRect textPos = QRect( PREVIEWCHANNELWIDTH/2, PREVIEWCHANNELHEIGTH/2, _size.width(), _size.height());

    switch( _mode ){

    case config:
        painter->drawText( textPos, QString::number( _channelNumber ) + " Config" );
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

void SinglePreviewChannelItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if( event->button() == Qt::RightButton )
    {
        _mode = config;
    }
    if( event->button() == Qt::LeftButton )
    {

    }

    event->accept();
}
