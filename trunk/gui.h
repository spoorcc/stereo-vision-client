#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

#include "Widgets/processstep.h"

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

    ProcessStep* _camera;
    ProcessStep* _rectfication;
    ProcessStep* _equalisation;

    void addElements();
    void printToConsole( QString message );
};

#endif // GUI_H
