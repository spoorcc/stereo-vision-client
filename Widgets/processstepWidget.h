#ifndef PROCESSSTEPWIDGET_H
#define PROCESSSTEPWIDGET_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The processstepWidget is a object which displays information about a single processstep

*/

// Global includes
#include <QWidget>

// Local includes
#include "DataTypes/processstep.h"

namespace Ui {
    class ProcessStepWidget;
}

class ProcessStepWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ProcessStepWidget( ProcessStep* processStep, QWidget *parent = 0);
    ~ProcessStepWidget();

    void setName(QString name);
    
private:
    Ui::ProcessStepWidget *ui;
};

#endif // PROCESSSTEPWIDGET_H
