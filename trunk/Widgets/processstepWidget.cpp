#include "processstepWidget.h"
#include "ui_processstepWidget.h"

ProcessStepWidget::ProcessStepWidget(ProcessStep *processStep, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessStepWidget)
{
    ui->setupUi(this);

    setName( processStep->name() );
    setParameters( processStep );

}

ProcessStepWidget::~ProcessStepWidget()
{
    delete ui;
}
void ProcessStepWidget::setName(QString name)
{
    ui->nameLBL->setText( name );
}

void ProcessStepWidget::setColor(QColor color)
{
    ui->nameLBL->setStyleSheet("QLabel { background-color: "+color.name()+"; }");
}

void ProcessStepWidget::setParameters(ProcessStep *processStep)
{
    QColor color = QColor( processStep->color() );

    this->setColor( color );
    for( int i = 0; i < processStep->numberOfParameters(); i++)
    {
        createParameter( processStep->parameter(i) );
    }
}

void ProcessStepWidget::createParameter(AbstractParameter *parameter)
{
    ParameterWidget* parWidget = new ParameterWidget( this );
    parWidget->setParameter( parameter );
    ui->parameterLayout->addWidget( parWidget );
}
