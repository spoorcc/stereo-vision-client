#ifndef GUI_H
#define GUI_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The gui gives the user the abilty to see the information and interact with it.

*/

#define DEFAULT_SERVER_IP   127.0.0.1
#define DEFAULT_SERVER_PORT 49679

// Global includes
#include <QMainWindow>
#include <QTime>
#include <QDir>
#include <QDesktopServices>
#include <QFileDialog>

//Local includes
#include "Widgets/processstepWidget.h"
#include "Widgets/connecttoserverdialog.h"

#include "Widgets/commandlinewidget.h"
#include "Widgets/previewwindow.h"

#include "Engine/commandlineparser.h"

namespace Ui {
    class GUI;
}

class GUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GUI(QWidget *parent = 0);
    ~GUI();



public slots:
    void start();
    void addProcessStep( ProcessStep* processStep );

    void printToConsole( QString sender, QString message );

    void connectDialogAccepted( QHostAddress address, quint16 port );
    void connectDialogRefused();

signals:
    void needAllProcessSteps();
    void connectToServer( QHostAddress address, quint16 port );
    void commandForServer( QString command );
    void setValueOnServer( QString processStep, QString parameter, QString value);
    void parseCommand( QString message );
    void makeEntry(QString entry);
    void saveLog();
    void setTargetDirectory(QString path);

private slots:
    void on_actionConnect_triggered();
    void createConnectToServerDialog(QHostAddress adress, quint16 port);

    void commandEnteredInCommandLine(QString command);
    void commandParsedAndChecked( QString command );

    bool getGuiCommand(QString command);

    void on_saveLogToFileBTN_clicked();

    void print(QString message);
    void printLastCommand(QString command, bool succesfull = true);

    void setValueOnGUI( QString processStep, QString parameter, QString value );
    void valueChangedOnGUI( QString processStep, QString parameter, QString value);
    void illegalUpdateOnGUI( QString message );

private:
    Ui::GUI *ui;

    CommandLineWidget* _commandLineWidget;
    CommandLineParser* _commandLineParser;
    PreviewWindow* _previewWindow;

    QTextStream _stream;
    QString _line;
  };

#endif // GUI_H
