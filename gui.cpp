#include "gui.h"
#include "ui_gui.h"


GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);

    //Add the windowicon
    this->setWindowIcon(QIcon(":/Icons/StereoVision.png"));

    //Add the commandline widget to the GUI
    _commandLineWidget = new CommandLineWidget(this);
    this->connect( _commandLineWidget, SIGNAL( executeCommand( QString) ), SLOT(commandEnteredInCommandLine(QString)) );
    this->connect( _commandLineWidget, SIGNAL( printToConsole(QString, QString)), SLOT( printToConsole(QString, QString) ));
    this->connect( _commandLineWidget, SIGNAL( set(QString,QString,QString)), SLOT(setValueOnGUI(QString,QString,QString)));
    this->connect( _commandLineWidget, SIGNAL( sendCommandToServer(QString)), SLOT(commandParsedAndChecked(QString)));
    this->connect( _commandLineWidget, SIGNAL( commandForGui(QString)), SLOT(getGuiCommand(QString)));
    this->connect( _commandLineWidget, SIGNAL(saveLog()), SLOT(on_saveLogToFileBTN_clicked()));
    ui->consoleCommandLO->addWidget( _commandLineWidget );

    //Add the previewwindow to the GUI
    _previewWindow = new PreviewWindow( this );
    _previewWindow->connect(this, SIGNAL(imageForPreviewWindow(QImage,int)),SLOT(imageForChannel(QImage, int)));
    this->connect( _previewWindow, SIGNAL(subscribeToStream( int, QString, QString, bool)),SIGNAL(subscribeToStream( int, QString, QString, bool)));
    this->connect( _previewWindow, SIGNAL(replaceStreamRequest(QString,QString,QImage*)), SIGNAL(replaceStreamRequest(QString,QString,QImage*)));
    _previewWindow->setObjectName("previewWindow");
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
        _previewWindow->addPreviewStream( processStep->name(), stream );
    }

    this->connect( processStepWidget, SIGNAL(valueChanged(QString,QString,QString)),SLOT(valueChangedOnGUI(QString,QString,QString)));
    this->connect( processStepWidget, SIGNAL(illegalUpdate(QString)),SLOT(illegalUpdateOnGUI(QString)));
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

void GUI::illegalUpdateOnGUI(QString message)
{
    printLastCommand( message, false);
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
    createConnectToServerDialog( QHostAddress(DEFAULT_SERVER_IP), DEFAULT_SERVER_PORT );
}
void GUI::createConnectToServerDialog( QHostAddress address, quint16 port)
{
    ConnectToServerDialog* dialog = new ConnectToServerDialog( address, port, this );

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
       // emit parseCommand( command );
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
        printLastCommand(command, true);
        printToConsole("GUI", "Cleared console");
        return true;
    }

    if( QString::compare( command, "Fullscreen",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "FLSCRN",Qt::CaseInsensitive ) == 0 )
    {
        printLastCommand(command, true);
        this->setWindowState(Qt::WindowFullScreen);
        printToConsole("GUI", "Window fullscreen");
        return true;
    }

    if( QString::compare( command, "Minimize",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "min",Qt::CaseInsensitive ) == 0 ||
        QString::compare( command, "MNMZ",Qt::CaseInsensitive ) == 0 )
    {
        printLastCommand(command, true);
        this->setWindowState(Qt::WindowMinimized);
        printToConsole("GUI", "Window minimized");
        return true;
    }

    if( QString::compare( command, "Maximize",Qt::CaseInsensitive) == 0 ||
        QString::compare( command, "max",Qt::CaseInsensitive ) == 0 ||
        QString::compare( command, "MXMZ",Qt::CaseInsensitive ) == 0 )
    {
        printLastCommand(command, true);
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

    if( QString::compare( command, "ORLY?",Qt::CaseInsensitive) == 0)
    {
        printLastCommand(command, true);
        printToConsole("Easter Egg", "YARLY!");
        return true;
    }
    if( QString::compare( command, "HERP?",Qt::CaseInsensitive) == 0)
    {
        printLastCommand(command, true);
        printToConsole("Easter Egg", "DERP!");
        return true;
    }
    if( QString::compare(command, "poep") == 0)
    {
        printLastCommand(command, true);
        printToConsole("Easter Egg", "Poep aan jou!");
        return true;
    }
    if( QString::compare(command, "save tonight",Qt::CaseInsensitive) == 0)
    {
        printLastCommand(command, true);
        printToConsole("Easter Egg", "and fight the break of dawn!");
        return true;
    }

    if( QString::compare( command, "credits",Qt::CaseInsensitive) == 0)
    {
        printLastCommand(command, true);
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

    if( QString::compare( commandParts.at(0),"TAB", Qt::CaseInsensitive) == 0)
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

    if( QString::compare( commandParts.at(0), "Connect to server",Qt::CaseInsensitive) == 0 ||
        QString::compare( commandParts.at(0), "c2s",Qt::CaseInsensitive) == 0 ||
        QString::compare( commandParts.at(0), "Server Connect",Qt::CaseInsensitive ) == 0 )
    {
        QHostAddress address = QHostAddress( DEFAULT_SERVER_IP );
        quint16 port = DEFAULT_SERVER_PORT;

        if( commandParts.count() > 1)
        {
            if(!QHostAddress( commandParts.at(1) ).isNull())
            {
                address = QHostAddress( commandParts.at(1) );
            }
            else
            {
                printLastCommand( commandParts.at(1) + " is not a valid IPv4 address", false);
            }
        }
        if( commandParts.count() > 2)
        {
            port = commandParts.at(2).toInt();
        }

        createConnectToServerDialog( address, port);

        printLastCommand(command, true);
        return true;
    }

    printLastCommand( command,  false );
    return false;
}

void GUI::on_saveLogToFileBTN_clicked()
{
    QFileDialog *dialogWindow = new QFileDialog();
    QString dir = dialogWindow->getExistingDirectory(this, tr("Choose folder"), qgetenv("HOME"));
    emit setTargetDirectory(dir);
    emit saveLog();
}
void GUI::statusBarMessage( QString message )
{
    ui->statusBar->showMessage( message, 5);
}
