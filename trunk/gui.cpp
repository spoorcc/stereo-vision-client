#include "gui.h"
#include "ui_gui.h"


GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);

    //Add the windowicon
    this->setWindowIcon(QIcon(":/Icons/StereoVision.png"));

    //Add the commandlind widget to the GUI
    _commandLineWidget = new CommandLineWidget(this);
    this->connect( _commandLineWidget, SIGNAL( executeCommand( QString) ), SLOT(commandEnteredInCommandLine(QString)) );
    this->connect( _commandLineWidget, SIGNAL( printToConsole(QString, QString)), SLOT( printToConsole(QString, QString) ));
    this->connect( _commandLineWidget, SIGNAL( set(QString,QString,QString)), SLOT(setValueOnGUI(QString,QString,QString)));
    this->connect( _commandLineWidget, SIGNAL( sendCommandToServer(QString)), SLOT(commandParsedAndChecked(QString)));
    this->connect( _commandLineWidget, SIGNAL( commandForGui(QString)), SLOT(getGuiCommand(QString)));
    ui->consoleCommandLO->addWidget( _commandLineWidget );

    //Add the previewwindow to the GUI
    _previewWindow = new PreviewWindow( this );
    ui->previewWindowLO->addWidget( _previewWindow );

    this->setWindowTitle( "Stereo vision client" );
    _commandLineWidget->setFocus();
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
    processStepWidget->setObjectName( processStep->name() );
    ui->AllProcessesTBX->addItem( processStepWidget, processStep->name() );

    if( ui->AllProcessesTBX->itemText(0) == "" )
    {
        ui->AllProcessesTBX->removeItem( 0 );
    }

    QStringList streamList = processStep->inputStreams();
    streamList.append( processStep->outputStreams() );

    foreach( QString stream, streamList)
    {
        stream.prepend( processStep->name() + " - ");
        _previewWindow->addVideoStream( stream );
    }

    this->connect( processStepWidget, SIGNAL(valueChanged(QString,QString,QString)),SLOT(valueChangedOnGUI(QString,QString,QString)));
    print( "Added step:" + processStep->name() );
}
void GUI::print( QString message )
{
    printToConsole("GUI", message);
}

void GUI::printToConsole( QString sender,  QString message )
{
    QString time = "<b>" + QTime::currentTime().toString() + "</b>" ;
    QString entry = QString( time + " ["+ sender+ "] " +  message );
    ui->console->append( entry );
    emit makeEntry( entry );
}

void GUI::printLastCommand( QString command, bool succesfull)
{
    if(succesfull)
    {
        command.prepend("<font color=\"green\">>>");
    }
    else
    {
        command.prepend("<font color=\"red\">>>");
    }
    command.append("</font>");
    printToConsole("Command", command);
}

void GUI::setValueOnGUI(QString processStep, QString parameter, QString value)
{
    for( int i = 0; i < ui->AllProcessesTBX->count(); i++ )
    {
        if( ui->AllProcessesTBX->widget(i)->objectName() == processStep )
        {
            QWidget* processStepWidget =  ui->AllProcessesTBX->widget(i);
            ((ProcessStepWidget*) processStepWidget)->setParameter( parameter, value);
            return;
        }
    }
    printLastCommand("No such processStep " + processStep, false);
}

void GUI::valueChangedOnGUI(QString processStep, QString parameter, QString value)
{
    printLastCommand( QString("Sent new value to server %1 %2 %3").arg(processStep, parameter,value), true);
    emit setValueOnServer( processStep, parameter, value);
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
    if( getGuiCommand(command) )
    {
        return;
    }
    else
    {
        emit parseCommand( command );
    }
}

void GUI::commandParsedAndChecked(QString command)
{
    emit commandForServer( command );
}
bool GUI::getGuiCommand(QString command)
{
    if( QString::compare(command, "clc") == 0 ||
        QString::compare(command, "clear") == 0 ||
        QString::compare(command, "console clear") == 0)
    {
        ui->console->clear();
        printLastCommand(command);
        printToConsole("GUI", "Cleared console");
        return true;
    }


    if( QString::compare( command, "Fullscreen",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "FLSCRN",Qt::CaseInsensitive ) == 0 )
    {
        printLastCommand(command);
        this->setWindowState(Qt::WindowFullScreen);
        printToConsole("GUI", "Window fullscreen");
        return true;
    }

    if( QString::compare( command, "Minimize",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "min",Qt::CaseInsensitive ) == 0 ||
        QString::compare( command, "MNMZ",Qt::CaseInsensitive ) == 0 )
    {
        printLastCommand(command);
        this->setWindowState(Qt::WindowMinimized);
        printToConsole("GUI", "Window minimized");
        return true;
    }

    if( QString::compare( command, "Maximize",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "max",Qt::CaseInsensitive ) == 0 ||
        QString::compare( command, "MXMZ",Qt::CaseInsensitive ) == 0 )
    {
        printLastCommand(command);
        this->setWindowState(Qt::WindowMaximized);
        printToConsole("GUI", "Window maximized");
        return true;
    }

    if( QString::compare( command, "Maximize",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "Maximise",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "MXMZ",Qt::CaseInsensitive ) == 0 )
    {
        printLastCommand(command);
        this->setWindowState(Qt::WindowMaximized);
        printToConsole("GUI", "Window maximized");
        return true;
    }


    if( QString::compare( command, "Close",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "Terminate",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "I love apple",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "apple",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "exit",Qt::CaseInsensitive ) == 0 )
    {
        this->close();
        return true;
    }

    if( QString::compare( command, "Connect to server",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "c2s",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "Server Connect",Qt::CaseInsensitive ) == 0 )
    {
        printLastCommand(command);
        this->on_actionConnect_triggered();
        return true;
    }
    if( QString::compare( command, "ORLY?",Qt::CaseInsensitive) == 0)
    {
        printLastCommand(command);
        printToConsole("Easter Egg", "YARLY!");
        return true;
    }
    if( QString::compare( command, "HERP?",Qt::CaseInsensitive) == 0)
    {
        printLastCommand(command);
        printToConsole("Easter Egg", "DERP!");
        return true;
    }
    if( QString::compare(command, "poep") == 0)
    {
        printLastCommand(command);
        printToConsole("Easter Egg", "Poep aan jou!");
        return true;
    }
    if( QString::compare(command, "save tonight",Qt::CaseInsensitive) == 0)
    {
        printLastCommand(command);
        printToConsole("Easter Egg", "and fight the break of dawn!");
        return true;
    }

    if( QString::compare( command, "credits",Qt::CaseInsensitive) == 0)
    {
        printLastCommand(command);
        printToConsole("The Almighty", "Android Crew");
        printToConsole("The Cranky", "Nick van Tilborg");
        printToConsole("The Drunk", "Bjeurn de Ruiter");
        printToConsole("The EXCELLent", "Maurice Nijkamp");
        printToConsole("The Nerdy", "Ben Spoor");
        printToConsole("The Hotty", "Tristan Frijters");
        return true;
    }

    // Select Tab
    QStringList commandParts = command.split(" ");

    if( QString::compare( commandParts.at(0),"TAB") == 0)
    {
        for(int i = 0; i < ui->AllProcessesTBX->count();i++)
        {
            if( QString::compare( commandParts.at(1),ui->AllProcessesTBX->itemText(i), Qt::CaseInsensitive) == 0)
            {
                ui->AllProcessesTBX->setCurrentIndex(i);
                printLastCommand(command);
                printToConsole("Interface", "" + ui->AllProcessesTBX->itemText(i) + " tab selected");
                return true;
            }
            else if(i == ui->AllProcessesTBX->count() - 1 )
            {
                printLastCommand(command,false);
                printToConsole("Interface", "Invalid tab");
            }
        }
        return true;
    }
    return false;
}

void GUI::on_saveLogToFileBTN_clicked()
{
    emit saveLog();
}
