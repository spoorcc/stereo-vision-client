#include "gui.h"
#include "ui_gui.h"


GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    _camera = new ProcessStepWidget();
    _rectfication = new ProcessStepWidget();
    _equalisation = new ProcessStepWidget();

    addElements();
}

GUI::~GUI()
{
    delete ui;
}

void GUI::addElements()
{
    _camera->setName( "Camera's" );
    _rectfication->setName( "Rectification" );
    _equalisation->setName( "Equalisation" );

    ui->processtepLO->addWidget(_camera,1,1);
    ui->processtepLO->addWidget(_rectfication,1,2);
    ui->processtepLO->addWidget(_equalisation,1,3);

    printToConsole( "Added elements!" );
}

void GUI::printToConsole( QString message )
{
    ui->console->append( "[GUI] :" +  message );
}
