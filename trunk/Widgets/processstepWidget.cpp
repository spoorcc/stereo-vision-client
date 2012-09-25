#include "processstepWidget.h"
#include "ui_processstepWidget.h"

ProcessStepWidget::ProcessStepWidget(ProcessStep *processStep, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessStepWidget)
{
    ui->setupUi(this);

    setName( processStep->name() );
}

ProcessStepWidget::~ProcessStepWidget()
{
    delete ui;
}
void ProcessStepWidget::setName(QString name)
{
    ui->nameLBL->setText( name );
}
