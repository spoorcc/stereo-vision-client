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
    void addProcessStep( ProcessStep* processStep );
    void printToConsole( QString sender, QString message );

signals:
    void needAllProcessSteps();
    
private:
    Ui::GUI *ui;

    void print(QString message);
};

#endif // GUI_H
