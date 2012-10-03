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
    
private slots:
    void on_actionConnect_triggered();

private:
    Ui::GUI *ui;

    CommandLineWidget* _commandLineWidget;
    PreviewWindow* _previewWindow;
    void print(QString message);
};

#endif // GUI_H
