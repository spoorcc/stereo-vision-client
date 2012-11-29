#ifndef PREVIEWCHANNEL_H
#define PREVIEWCHANNEL_H

#include <QDebug>

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

class PreviewChannel : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:

    PreviewChannel( QRectF dimensions, int id );

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setText( QString text);
    void setImage(QImage *image);

    void setVisible( bool tf );

    int id();

signals:
    void replaceStreamRequest();
    void previewStreamRequest( int id, QString processStep, QString streamName, bool continous);

public slots:
    void addStream( QString processStep, QString streamName );

private slots:
    void menuClickHandler(QAction *action);

private:
    void initMenus();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    QRectF _boundingRect;
    QString _text;
    QMenu* _selectStreams;
    QMenu* _streamOptions;

    bool _visible;

    QImage* _image;

    int _id;
};

#endif // PREVIEWCHANNEL_H
