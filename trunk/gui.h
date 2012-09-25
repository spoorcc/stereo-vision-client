#ifndef GUI_H
#define GUI_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The gui gives the user the abilty to see the information and interact with it.

*/

// Global includes
#include <QMainWindow>

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
    
private:
    Ui::GUI *ui;

    ProcessStepWidget* _camera;
    ProcessStepWidget* _rectfication;
    ProcessStepWidget* _equalisation;

    void addElements();
    void printToConsole( QString message );
};

#endif // GUI_H
