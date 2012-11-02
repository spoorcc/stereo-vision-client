#ifndef GUI_H
#define GUI_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The gui gives the user the abilty to see the information and interact with it.

*/

// Global includes
#include <QMainWindow>
#include <QTime>

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
    void parseCommand( QString message );
    void makeEntry(QString entry);
    void saveLog();

private slots:
    void on_actionConnect_triggered();
    void commandEnteredInCommandLine(QString command);
    void commandParsedAndChecked( QString command );

    bool getGuiCommand(QString command);

    void on_saveLogToFileBTN_clicked();

    void print(QString message);
    void printLastCommand(QString command, bool succesfull = true);

    void set( QString processStep, QString parameter, QString value );

private:
    Ui::GUI *ui;

    CommandLineWidget* _commandLineWidget;
    CommandLineParser* _commandLineParser;
    PreviewWindow* _previewWindow;    

};

#endif // GUI_H
