#include "commandlinewidget.h"
#include "ui_commandlinewidget.h"

CommandLineWidget::CommandLineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandLineWidget)
{
    ui->setupUi(this);
    ui->commandLE->setFocus();

}

CommandLineWidget::~CommandLineWidget()
{
    delete ui;
}

void CommandLineWidget::on_commandPB_clicked()
{
    sendCommand();
}

void CommandLineWidget::on_commandLE_returnPressed()
{
    sendCommand();
}

void CommandLineWidget::sendCommand()
{
    if (ui->commandLE->text().count() > 0)
    {
        emit executeCommand( ui->commandLE->text() );
        ui->commandLE->clear();
    }
}

