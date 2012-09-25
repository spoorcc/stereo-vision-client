#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The parameter widget contains one parameter and is changeable by the user, when changed it emits a signalso that the gui can send the update info to the engine

*/
#include <QWidget>

namespace Ui {
class ParameterWidget;
}

class ParameterWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ParameterWidget(QWidget *parent = 0);
    ~ParameterWidget();
    
private:
    Ui::ParameterWidget *ui;
};

#endif // PARAMETERWIDGET_H
