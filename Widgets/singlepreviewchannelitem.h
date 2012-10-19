#ifndef SINGLEPREVIEWCHANNELITEM_H
#define SINGLEPREVIEWCHANNELITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRect>
#include <QComboBox>

#define PREVIEWCHANNELWIDTH  320
#define PREVIEWCHANNELHEIGTH 240

class SinglePreviewChannelItem : public QGraphicsItem
{
public:

    enum Mode { config, preview, replace};

    SinglePreviewChannelItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget *widget);
    
    void setChannelNumber(int number);

    int channelNumber();
    void setMode(SinglePreviewChannelItem::Mode mode);
signals:
    
public slots:

private:
    QRect _size;
    int _channelNumber;
    SinglePreviewChannelItem::Mode _mode;
};

#endif // SINGLEPREVIEWCHANNELITEM_H
