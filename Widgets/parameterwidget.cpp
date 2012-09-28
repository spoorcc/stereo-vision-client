#include "parameterwidget.h"
#include "ui_parameterwidget.h"

ParameterWidget::ParameterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterWidget)
{
    ui->setupUi(this);
}

ParameterWidget::~ParameterWidget()
{
    delete ui;
}

void ParameterWidget::setParameter(AbstractParameter *parameter)
{
    if( parameter->isBoolean() )
    {
        createBooleanWidget( parameter );
    }
    if( parameter->isNumerical() )
    {
        createNumericWidget( parameter );
    }
    if( parameter->isSelect() )
    {
        createSelectWidget( parameter );
    }
}

void ParameterWidget::createBooleanWidget(AbstractParameter *parameter)
{
    // Set the name of the parameter
    ui->nameLBL->setText( "Boolean " + ((BooleanParameter*) parameter)->name() );

    //Create a checkbox and add one
    QCheckBox* checkBox = new QCheckBox (this);
    ui->horizontalLayout->addWidget(checkBox);

    //For better layout, create a spacer
    QSpacerItem* horizontalSpacer = new QSpacerItem (10,10, QSizePolicy::Expanding);
    ui->horizontalLayout->addSpacerItem(horizontalSpacer);
}

void ParameterWidget::createNumericWidget(AbstractParameter *parameter)
{
    ui->nameLBL->setText( "Numberic " + ((NumericParameter*) parameter)->name() );
}
void ParameterWidget::createSelectWidget( AbstractParameter *parameter)
{
    ui->nameLBL->setText( "Select " + ( (SelectParameter*) parameter)->name() );
}
