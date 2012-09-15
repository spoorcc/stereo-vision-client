#include "processstep.h"
#include "ui_processstep.h"

ProcessStep::ProcessStep(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessStep)
{
    ui->setupUi(this);
}

ProcessStep::~ProcessStep()
{
    delete ui;
}
void ProcessStep::setName(QString name)
{
    ui->nameLBL->setText( name );
}
