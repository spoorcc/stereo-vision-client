#include "gui.h"
#include "ui_gui.h"


GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);

}

GUI::~GUI()
{
    delete ui;
}
void GUI::start()
{
    print("Requested processSteps");
    emit needAllProcessSteps();
}

void GUI::addProcessStep(ProcessStep *processStep)
{
    ProcessStepWidget* processStepWidget = new ProcessStepWidget( processStep, this );
    ui->AllProcessesTBX->addItem( processStepWidget, processStep->name() );

    print( "Added step:" + processStep->name() );
}
void GUI::print( QString message )
{
    printToConsole("GUI", message);
}

void GUI::printToConsole( QString sender,  QString message )
{
    QString time = QTime::currentTime().toString();
    ui->console->append( time + " ["+ sender+ "] " +  message );
}

void GUI::connectDialogAccepted(QHostAddress address, quint16 port)
{
    print("Giving command to connect to transciever at " + address.toString() + " on port " + QString::number( port ) );
    emit connectToServer( address, port );
}

void GUI::connectDialogRefused()
{
    print("Connect to server dialog closed");
}

void GUI::on_actionConnect_triggered()
{
    print("Opening connect to server dialog");
    ConnectToServerDialog* dialog = new ConnectToServerDialog( QHostAddress("127.0.0.1"),7755);

    this->connect( dialog, SIGNAL( connectToServer(QHostAddress,quint16) ) , this, SLOT( connectDialogAccepted(QHostAddress,quint16) ) );
    this->connect( dialog, SIGNAL( rejected() ), this,  SLOT(connectDialogRefused()) );

    dialog->show();
}
