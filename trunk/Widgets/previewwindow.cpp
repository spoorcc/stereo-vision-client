#include "previewwindow.h"
#include "ui_previewwindow.h"

PreviewWindow::PreviewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewWindow)
{
    ui->setupUi(this);

    _scene = new QGraphicsScene( this );

    ui->previewWindowGV->setScene( _scene );
}

PreviewWindow::~PreviewWindow()
{
    delete ui;
}
