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
    ui->nameLBL->setToolTip( parameter->description() );
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
    ui->nameLBL->setText( ((BooleanParameter*) parameter)->name() );

    //Create a checkbox and add one
    QCheckBox* checkBox = new QCheckBox (this);
    ui->horizontalLayout->addWidget(checkBox);

    addSpacer();
}

void ParameterWidget::createNumericWidget(AbstractParameter *parameter)
{
    ui->nameLBL->setText( ((NumericParameter*) parameter)->name() );

    //Create a spinbox

    QSpinBox* spinBox = new QSpinBox(this);
    spinBox->setMaximum( ((NumericParameter*)parameter)->maximum() );
    spinBox->setMinimum( ((NumericParameter*)parameter)->minimum() );
    spinBox->setValue( ((NumericParameter*)parameter)->init());
    ui->horizontalLayout->addWidget(spinBox);

    addSpacer();
}
void ParameterWidget::createSelectWidget( AbstractParameter *parameter)
{
    ui->nameLBL->setText( ( (SelectParameter*) parameter)->name() );

    //Create a combobox
    QComboBox* comboBox = new QComboBox(this);
    comboBox->setToolTip( parameter->description() );

    for( int i = 0; i < ((SelectParameter*) parameter)->count(); i++ )
    {
        comboBox->addItem( ((SelectParameter*) parameter)->option(i) );
    }

    ui->horizontalLayout->addWidget( comboBox );

    addSpacer();
}
void ParameterWidget::addSpacer()
{
    //For better layout, create a spacer
    QSpacerItem* horizontalSpacer = new QSpacerItem (10,10, QSizePolicy::Expanding);
    ui->horizontalLayout->addSpacerItem(horizontalSpacer);
}

