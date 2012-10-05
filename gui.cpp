#include "gui.h"
#include "ui_gui.h"


GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);

    //Add the commandlind widget to the GUI
    _commandLineWidget = new CommandLineWidget(this);
    this->connect( _commandLineWidget, SIGNAL( executeCommand( QString) ), SLOT(commandEnteredInCommandLine(QString)) );
    ui->consoleCommandLO->addWidget( _commandLineWidget );

    //Add the previewwindow to the GUI
    _previewWindow = new PreviewWindow( this );
    ui->previewWindowLO->addWidget( _previewWindow );

    this->setWindowTitle( "Stereo vision client" );
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


    if( ui->AllProcessesTBX->itemText(0) == "" )
    {
        ui->AllProcessesTBX->removeItem( 0 );
    }

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
void GUI::commandEnteredInCommandLine(QString command)
{
    if( isGuiCommand(command) )
    {
        return;
    }
    else
    {
        emit parseCommand( command );
    }
}
bool GUI::isGuiCommand(QString command)
{
    if( QString::compare(command, "clc") == 0)
    {
        ui->console->clear();
        printToConsole("GUI", "Cleared console");
        return true;
    }
    if( QString::compare(command, "poep") == 0)
    {
        printToConsole("Easter Egg", "Poep aan jou!");
        return true;
    }

    return false;

}
