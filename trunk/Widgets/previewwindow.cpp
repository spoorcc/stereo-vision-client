#include "previewwindow.h"
#include "ui_previewwindow.h"

PreviewWindow::PreviewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewWindow)
{
    _mode = PreviewWindow::configMode;

    ui->setupUi(this);

    createScene();

    ui->previewWindowGV->setScene( _scene );
    ui->previewWindowGV->show();

   // this->connect( _previewChannels.first(), SIGNAL())

}

PreviewWindow::~PreviewWindow()
{
    delete ui;
}

void PreviewWindow::createScene()
{
    _scene = new QGraphicsScene( this );

    _scene->setSceneRect( 0, 0, 4 * PREVIEWCHANNELWIDTH, 2 * PREVIEWCHANNELHEIGTH );

    for( int i = 0; i < 8; i++ )
    {
        SinglePreviewChannelItem* previewChannel = new SinglePreviewChannelItem();

        previewChannel->setChannelNumber( i );
        previewChannel->setPos(( i%2 )* PREVIEWCHANNELWIDTH + (i/4) * 2 * PREVIEWCHANNELWIDTH, ( (i/2)* PREVIEWCHANNELHEIGTH) % (2 * PREVIEWCHANNELHEIGTH)) ;

        _previewChannels.append( previewChannel );

        _scene->addItem( previewChannel );

        QComboBox* streamSelectCB = new QComboBox();
        streamSelectCB->setBaseSize(PREVIEWCHANNELWIDTH/2,PREVIEWCHANNELHEIGTH/6);
        QPointF absPos = previewChannel->pos();
        QPointF relPos = QPointF( PREVIEWCHANNELWIDTH/4, PREVIEWCHANNELHEIGTH/6);

        _videoStreamCB.append( streamSelectCB );

        QGraphicsProxyWidget* proxy = _scene->addWidget( streamSelectCB );
        proxy->setPos( (absPos += relPos) );
    }

}
void PreviewWindow::drawConfigScreen()
{
    _scene->setSceneRect( 0, 0, 4 * PREVIEWCHANNELWIDTH, 2 * PREVIEWCHANNELHEIGTH );
    makeChannelsUnvisible(8);

    ui->previewWindowGV->update();

}

void PreviewWindow::drawSingleView()
{
    _scene->setSceneRect( 0, 0, PREVIEWCHANNELWIDTH, PREVIEWCHANNELHEIGTH);
    makeChannelsUnvisible(1);
}

void PreviewWindow::drawDualView()
{
    _scene->setSceneRect(0,0,2 * PREVIEWCHANNELWIDTH, PREVIEWCHANNELHEIGTH);
    makeChannelsUnvisible(2);
}

void PreviewWindow::drawQuadView()
{
    _scene->setSceneRect(0,0, 2 * PREVIEWCHANNELWIDTH, 2 * PREVIEWCHANNELHEIGTH);
    makeChannelsUnvisible(4);
}

void PreviewWindow::drawOctoView()
{
    _scene->setSceneRect(0,0,4 * PREVIEWCHANNELWIDTH, 2 * PREVIEWCHANNELHEIGTH);
    makeChannelsUnvisible(8);
    ui->previewWindowGV->update();
}

void PreviewWindow::makeChannelsUnvisible( int index )
{
    for( int i = 0; i < _previewChannels.count(); i++)
    {
        bool visible = true;
        if( i >= index)
        {
            visible = false;
        }
        _previewChannels.at(i)->setVisible( visible );
    }
}

void PreviewWindow::addImage( QPixmap image )
{
    _scene->addPixmap( image );
}

void PreviewWindow::clearAll()
{
    _scene->clear();
}

void PreviewWindow::scaleForMode( PreviewWindow::Mode previous, PreviewWindow::Mode next )
{
    double scaleX = 1.0;
    double scaleY = 1.0;

    switch( previous ){

        case singleView:
            scaleX = 0.25;
            scaleY = 0.50;
            break;

        case dualView:
            scaleX = 0.50;
            scaleY = 0.50;
            break;

        case quadView:
            scaleX = 0.50;
            scaleY = 1.0;
            break;
        default:
            scaleX = 1.0;
            scaleY = 1.0;
     }

    ui->previewWindowGV->scale(scaleX, scaleY);

    switch( next ){
        case singleView:
            scaleX = 4.0;
            scaleY = 2.0;
            break;

        case dualView:
            scaleX = 2.0;
            scaleY = 2.0;
            break;

        case quadView:
            scaleX = 2.0;
            scaleY = 1.0;
            break;
        default:
            scaleX = 1.0;
            scaleY = 1.0;
     }

    ui->previewWindowGV->scale(scaleX, scaleY);

}

void PreviewWindow::on_configPB_clicked()
{
    if(_mode != configMode)
    {
        scaleForMode( _mode, configMode);
        _mode = configMode;
        ui->modeCB->setVisible(true);
        ui->configPB->setText("Preview mode");

        foreach( SinglePreviewChannelItem* item, _previewChannels)
        {
            item->setMode( SinglePreviewChannelItem::config );
        }
        foreach( QComboBox* streamSelectCB, _videoStreamCB )
        {
            streamSelectCB->setVisible( true );
        }
        drawConfigScreen();
    }
    else
    {
        _mode = Mode( ui->modeCB->currentIndex() );
        ui->modeCB->setVisible(false);

        foreach( QComboBox* streamSelectCB, _videoStreamCB )
        {
            streamSelectCB->setVisible(false);
        }

        switch( _mode ){

        case singleView:
            drawSingleView();
            break;
        case dualView:
            drawDualView();
            break;
        case quadView:
            drawQuadView();
            break;
        case octoView:
            drawOctoView();
            break;
        default:
            drawOctoView();
            break;
        }

        foreach( SinglePreviewChannelItem* item, _previewChannels)
        {
            item->setMode( SinglePreviewChannelItem::preview );
        }

        scaleForMode( configMode, _mode);
        ui->configPB->setText("Config mode");
    }
}

void PreviewWindow::addVideoStream(QString streamName)
{
    foreach( QComboBox* streamSelectCB, _videoStreamCB)
    {
        streamSelectCB->addItem( streamName );
    }
}
/*void PreviewWindow::keyEventListener( QKeyEvent event)
{
    qDebug() << event;
}*/

void PreviewWindow::on_previewWindowGV_customContextMenuRequested(const QPoint &pos)
{
    qDebug() << "Mouseclick";
}
