#include "previewwindow.h"
#include "ui_previewwindow.h"

PreviewWindow::PreviewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewWindow)
{
    ui->setupUi(this);

    disableScrollBars();

    initChannelCountBox();
    initPreviewScene();
    initPreviewChannels();
}

PreviewWindow::~PreviewWindow()
{
    delete ui;
}
void PreviewWindow::disableScrollBars()
{
    ui->previewWindowGV->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    ui->previewWindowGV->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
}

void PreviewWindow::initChannelCountBox()
{
    ui->modeCB->addItem("Single view", 1);
    ui->modeCB->addItem("Dual view", 2);
    ui->modeCB->addItem("Quad view", 4);
    ui->modeCB->addItem("Octo view", 8);
}

void PreviewWindow::initPreviewScene()
{
    _previewScene = new QGraphicsScene(this);

    QRectF sceneRect = QRectF(-CHANNELWIDTH/2,-CHANNELHEIGTH/2, CHANNELWIDTH * (HORCHANNELCOUNT + 1), CHANNELHEIGTH * (VERCHANNELCOUNT + 1) );
    _previewScene->setSceneRect( sceneRect );

    ui->previewWindowGV->setScene( _previewScene );
}

void PreviewWindow::initPreviewChannels()
{
    for( int i = 0; i < (HORCHANNELCOUNT * VERCHANNELCOUNT); i++)
    {
        QRectF channelDim = QRect( (i%HORCHANNELCOUNT) * CHANNELWIDTH,
                                  (i/HORCHANNELCOUNT) * CHANNELHEIGTH,
                                  CHANNELWIDTH, CHANNELHEIGTH);
        QString channel = QString("Channel %1").arg(i);
        PreviewChannel* previewChannel = new PreviewChannel( channelDim, i );

        previewChannel->setText( channel  );
        this->connect( previewChannel, SIGNAL( subscribeToStream(int,QString,QString,bool)),SIGNAL(subscribeToStream(int,QString,QString,bool)));
        this->connect( previewChannel, SIGNAL(replaceStreamRequest(QString,QString,QImage*)), SIGNAL(replaceStreamRequest(QString,QString,QImage*)) );
        this->connect( previewChannel, SIGNAL(print(QString)), SIGNAL(print(QString)) );

        _previewScene->addItem( previewChannel );
        _previewChannels.append( previewChannel );
    }

}
void PreviewWindow::reset()
{
    _previewScene->clear();
    _previewChannels.clear();

    initChannelCountBox();
    initPreviewScene();
    initPreviewChannels();
}

void PreviewWindow::zoomToNumberOfChannels( int number )
{
    QList< int > channelIDs;

    switch( number )
    {
    case 1:
        channelIDs << 0;
        break;
    case 2:
        channelIDs << 0 << 1;
        break;
    case 4:
        channelIDs << 0 << 1 << 4 << 5;
        break;
    case 8:
        channelIDs << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7;
        break;
    default:
        channelIDs << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7;
        break;
    }

    selectChannels( channelIDs );
}

void PreviewWindow::selectChannels( QList<int> channelIDs )
{
    QRectF area;

    foreach( PreviewChannel* channel, _previewChannels )
    {
        if( channelIDs.contains( channel->id() ) )
        {
            channel->setVisible( true );
            area = area |= channel->boundingRect();
        }
        else
        {
            channel->setVisible(false);
        }
    }

    ui->previewWindowGV->fitInView( area, Qt::KeepAspectRatio );
}

void PreviewWindow::resizeEvent(QResizeEvent *)
{
    int channelCount = ui->modeCB->itemData( ui->modeCB->currentIndex() ).toInt();
    zoomToNumberOfChannels( channelCount );
}

void PreviewWindow::addPreviewStream(QString processStep, QString streamName)
{
    foreach( PreviewChannel* channel, _previewChannels)
    {
        channel->addStream( processStep, streamName );
    }
}

void PreviewWindow::on_modeCB_currentIndexChanged(int index)
{
    zoomToNumberOfChannels( ui->modeCB->itemData( index ).toInt() );
}
void PreviewWindow::imageForChannel( QImage image, int channelID )
{    
    _previewChannels.at(channelID)->setImage( image);

    ui->previewWindowGV->update();
}
