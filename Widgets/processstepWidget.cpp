#include "processstepWidget.h"
#include "ui_processstepWidget.h"

ProcessStepWidget::ProcessStepWidget(ProcessStep *processStep, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessStepWidget)
{
    ui->setupUi(this);

    ui->parameterLayout->setAlignment(Qt::AlignTop);
    ui->nameLBL->setAlignment(Qt::AlignCenter);
    ui->nameLBL->setMinimumWidth(120);
    _styleSheet = "font: 15pt;border-style: outset; border-width: 2px; border-radius: 10px; border-color: black;";

    _inputStreamWidget = new StreamSelectWidget(this);
    _outputStreamWidget = new StreamSelectWidget (this);

    _inputStreamWidget->setAsInput();
    _outputStreamWidget->setAsOutput();

    _inputStreamWidget->setStreams( processStep->inputStreams() );
    _outputStreamWidget->setStreams( processStep->outputStreams() );

    ui->parameterLayout->addWidget( _inputStreamWidget );
    setName( processStep->name() );
    setParameters( processStep );
    ui->parameterLayout->addWidget( _outputStreamWidget);


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
    ui->nameLBL->setStyleSheet("QLabel { background-color: "+color.name()+";"+_styleSheet +"}");
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
    parWidget->setObjectName( parameter->name() );
    ui->parameterLayout->addWidget( parWidget );
}
void ProcessStepWidget::setParameter(QString parameter, QString value)
{
    for( int i = 0; i < ui->parameterLayout->count(); i++ )
    {
        if( ui->parameterLayout->itemAt(i)->widget()->objectName() == parameter )
        {
            QWidget* parameterWidget = (QWidget*) ui->parameterLayout->itemAt(i)->widget();
            qDebug() << ui->nameLBL->text() << parameter << value;
            ((ParameterWidget*) parameterWidget)->setValue( value );
            return;
        }
    }
    emit invalidUpdate( "No such parameter " + parameter );
}
