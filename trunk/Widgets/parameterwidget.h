#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  The parameter widget contains one parameter and is changeable by the user, when changed it emits a signalso that the gui can send the update info to the engine

*/

//Global includes
#include <QWidget>
#include <QCheckBox>
#include <QSpacerItem>

//Local includes
#include "DataTypes/allparametertypes.h"

namespace Ui {
class ParameterWidget;
}

class ParameterWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ParameterWidget(QWidget *parent = 0);
    ~ParameterWidget();

public slots:
    void setParameter( AbstractParameter* parameter );
    
signals:
    void valueChanged();

private:
    void createBooleanWidget( AbstractParameter* parameter );
    void createNumericWidget( AbstractParameter* parameter );
    void createSelectWidget( AbstractParameter* parameter );

    Ui::ParameterWidget *ui;
};

#endif // PARAMETERWIDGET_H
