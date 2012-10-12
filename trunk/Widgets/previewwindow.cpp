#include "previewwindow.h"
#include "ui_previewwindow.h"

PreviewWindow::PreviewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewWindow)
{
    ui->setupUi(this);

    createScene();

    ui->previewWindowGV->setScene( _scene );

}

PreviewWindow::~PreviewWindow()
{
    delete ui;
}

void PreviewWindow::createScene()
{
    _scene = new QGraphicsScene( this );


    int sceneHeight = _scene->height();
    int sceneWidth = _scene->width();

    int width = sceneWidth/4;
    int height = sceneHeight/2;

    for( int i = 0; i < 8; i++ )
    {
        _scene->addRect( ( i%4 ) * width, (i/4)* height, width, height  );
        QGraphicsSimpleTextItem* frameLabel = _scene->addSimpleText( QString("Frame " + QString::number(i) ) );
        frameLabel->setPos(  ( i%4 ) * width, (i/4)* height  );
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
void PreviewWindow::displayTwoImages( QPixmap image, QPixmap image2 )
{
    _scene->clear();
    _scene->addSimpleText( QString("Loading images"));

    addImage( image );
    addImage( image );
}
