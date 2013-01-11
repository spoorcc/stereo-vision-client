#include "previewchannel.h"

PreviewChannel::PreviewChannel(QRectF dimensions, int id)
{
    _id = id;

    _boundingRect = dimensions;
    _text = "";
    _image = new QImage("/home/ben/Dropbox/Studie/HexGridStraight.gif");
    _visible = true;

    _processStep = "<none>";
    _currentStream = "<none>";

    initMenus();
}
void PreviewChannel::initMenus()
{
    _selectStreams = new QMenu("Select Streams");

    _streamOptions = new QMenu("Stream options");
    QAction* saveImage  = _streamOptions->addAction("Save current image" );
    QAction* stopStream = _streamOptions->addAction("Stop current stream");
    QAction* replaceStream = _streamOptions->addAction("Replace current stream");

    QObject::connect( saveImage, SIGNAL(triggered()), this, SLOT( saveImageToFile() ));
    QObject::connect( stopStream, SIGNAL(triggered()), this, SLOT(stopCurrentStream()));
    QObject::connect( replaceStream, SIGNAL(triggered()), this, SLOT(replaceCurrentStream()));
}

QRectF PreviewChannel::boundingRect() const
{
    return _boundingRect ;
}

void PreviewChannel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if( _visible )
    {
        painter->drawImage( _boundingRect, *_image );
        painter->drawText( _boundingRect , _text );
        painter->drawRoundedRect( _boundingRect, 5, 5 );
    }
}
int PreviewChannel::id()
{
    return _id;
}

void PreviewChannel::setText(QString text)
{
    _text = text;
}
void PreviewChannel::setImage( QImage image )
{
    delete _image;
    _image = new QImage(image);

    qDebug() << "Setting image width" << image.size().width() << " height " << image.size().height() << " type ";
}

void PreviewChannel::setVisible(bool tf)
{
    _visible = tf;
}

void PreviewChannel::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu* menu = new QMenu();
    menu->addMenu( _selectStreams );
    menu->addMenu( _streamOptions );
    menu->popup( event->screenPos() );
}

void PreviewChannel::addStream(QString processStep, QString streamName)
{
    QMenu* processStepMenu = _selectStreams->findChild<QMenu*>( processStep );

    //If processStep is unique add it to _selectStream menu
    if( processStepMenu == 0 )
    {
        processStepMenu = _selectStreams->addMenu( processStep );
        processStepMenu->setParent( _selectStreams );
        processStepMenu->setObjectName( processStep );
    }

    QMenu* streamMenu = processStepMenu->findChild<QMenu*>( streamName );

    //If streamname is unique add it to processStepMenu
    if( streamMenu == 0 )
    {
        //Create the streammenu
        streamMenu = processStepMenu->addMenu( streamName );
        streamMenu->setParent( processStepMenu );
        streamMenu->setObjectName( streamName );

        //Create parameterlist for menu item
        QList< QVariant > actionInfo;
        actionInfo << processStep << streamName;

        //Add continous action to menu
        QAction* continousAction = new QAction("Continous", streamMenu);
        actionInfo.append("Continous");
        continousAction->setData( actionInfo );
        streamMenu->addAction( continousAction );

        //Add single shot action to menu
        QAction* singleShotAction = new QAction("Single shot", streamMenu);
        actionInfo.last().setValue( QString("Single shot") );
        singleShotAction->setData( actionInfo );
        streamMenu->addAction( singleShotAction );

        QObject::connect( streamMenu, SIGNAL( triggered(QAction*) ), this, SLOT( menuClickHandler(QAction*) ));
    }
}

void PreviewChannel::menuClickHandler(QAction* action)
{
    QVariant actionInfo = action->data();
    QList<QVariant> actionList = actionInfo.toList();

    _processStep = actionList.at(0).toString();
    _currentStream = actionList.at(1).toString();

    bool continous = (actionList.at(2).toString() == "Continous");

    _text = QString("Ch %1 - ProcessStep: %2 - Stream: %3 - [%4]").arg(_id).arg(_processStep).arg( _currentStream).arg(actionList.at(2).toString());

    emit subscribeToStream( _id, _processStep, _currentStream, continous );
}

void PreviewChannel::saveImageToFile()
{
    QFileDialog *dialogWindow = new QFileDialog();
    QString saveFileName =  dialogWindow->getSaveFileName(0,tr("Save image"));

    QImageWriter writer;
    writer.setFileName( saveFileName );
    writer.write( *_image );
}
void PreviewChannel::replaceCurrentStream()
{
    QFileDialog *dialogWindow = new QFileDialog();
    const QString& getFileName =  dialogWindow->getOpenFileName(0,tr("Open image"));

    _image->load( getFileName );

    _text = QString("Ch %1 - ProcessStep: %2 - Stream: %3 - [%4]").arg(_id).arg(_processStep).arg( _currentStream).arg("replaced");

    //emit replaceStreamRequest( streamName, *_image);
}

void PreviewChannel::stopCurrentStream()
{
    emit unsubscribeFromStream( _id);
}
