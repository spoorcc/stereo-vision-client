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
#include <QDir>
#include <QDesktopServices>
#include <QFileDialog>

//Local includes
#include "Widgets/ProcessesInputWidgets/processstepWidget.h"
#include "Widgets/Dialogs/connecttoserverdialog.h"

#include "Widgets/commandlinewidget.h"
#include "Widgets/PreviewWidget/previewwindow.h"

#include "Engine/commandlineparser.h"

#include "DataTypes/ClientServerProtocol.h"

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

    void statusBarMessage(QString message);

    void clearGui();

signals:
    void needAllProcessSteps();
    void connectToServer( QHostAddress address, quint16 port );
    void commandForServer( QString command );
    void setValueOnServer( QString processStep, QString parameter, QString value);

    void makeEntry(QString entry);
    void saveLog();
    void setTargetDirectory(QString path);

    void imageForPreviewWindow( QImage image, int channelId);
    void subscribeToStream( int channelId, QString processStep, QString streamName, bool continous);

    void replaceStreamRequest( QString processStep, QString streamName, QImage* image);

    void requestXML();
    void flushImageBuffers();

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

    void on_actionRequest_config_triggered();

private:
    Ui::GUI *ui;

    CommandLineWidget* _commandLineWidget;
    //CommandLineParser* _commandLineParser;
    PreviewWindow* _previewWindow;

    QTextStream _stream;
    QString _line;
  };

#endif // GUI_H
