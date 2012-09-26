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
}

void ParameterWidget::createBooleanWidget(AbstractParameter *parameter)
{
    ui->nameLBL->setText( "Boolean " + ((BooleanParameter*) parameter)->name() );
}

void ParameterWidget::createNumericWidget(AbstractParameter *parameter)
{
    ui->nameLBL->setText( "Numberic " + ((NumericParameter*) parameter)->name() );
}
