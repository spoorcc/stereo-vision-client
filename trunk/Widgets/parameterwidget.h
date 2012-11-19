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
#include <QComboBox>
#include <QSpacerItem>
#include <QSpinBox>

#include <QDebug>

//Local includes
#include "DataTypes/allparametertypes.h"

enum parameterWidgetType{ BOOLEAN, NUMERICAL, SELECTABLE, UNKWOWN };

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
    void setValue( QString value );
    void setParameter(AbstractParameter *parameter);
    
signals:
    void valueChanged(QString name, QString value);

private:
    void createBooleanWidget( AbstractParameter* parameter );
    void createNumericWidget( AbstractParameter* parameter );
    void createSelectWidget( AbstractParameter* parameter );

    void setBooleanValue(QString value);
    void setNumericalValue(QString value);
    void setSelectableValue(QString value);

    void addSpacer();

    Ui::ParameterWidget *ui;

    parameterWidgetType _type;
};

#endif // PARAMETERWIDGET_H
