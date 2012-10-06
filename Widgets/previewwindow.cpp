#include "previewwindow.h"
#include "ui_previewwindow.h"

PreviewWindow::PreviewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewWindow)
{
    ui->setupUi(this);

    _scene = new QGraphicsScene( this );

    ui->previewWindowGV->setScene( _scene );
    _scene->addSimpleText( QString("No images loaded") );
}

PreviewWindow::~PreviewWindow()
{
    delete ui;
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
