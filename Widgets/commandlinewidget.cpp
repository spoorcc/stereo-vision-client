#include "commandlinewidget.h"
#include "ui_commandlinewidget.h"

CommandLineWidget::CommandLineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandLineWidget)
{
    ui->setupUi(this);
    this->setFocusPolicy( Qt::StrongFocus );
    ui->commandLE->installEventFilter(this);
    _commandIndex = 0;

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

bool CommandLineWidget::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui->commandLE)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Up)
            {
                 _commandIndex++;
                 if(_commandIndex > _commandHistory.count())
                 {
                     _commandIndex = _commandHistory.count();
                 }
                 setOldCommand();
                 return true;
            }
            else if(keyEvent->key() == Qt::Key_Down)
            {
                _commandIndex--;
                if(_commandIndex < 0)
                {
                    _commandIndex = 0;
                }
                setOldCommand();
                return true;
            }
        }
        return false;
    }
    return CommandLineWidget::eventFilter(obj, event);
}

void CommandLineWidget::setOldCommand()
{
    ui->commandLE->setText( _commandHistory.at( _commandIndex));
}

void CommandLineWidget::sendCommand()
{
    if (ui->commandLE->text().count() > 0)
    {
        emit executeCommand( ui->commandLE->text() );
        ui->commandLE->clear();
        _commandHistory.prepend(ui->commandLE->text());
        if (_commandHistory.size()>100)
        {
            _commandHistory.pop_back();
        }
    }
}
void CommandLineWidget::focusInEvent(QFocusEvent *)
{
    //If the commandline widget gets focus itgives focus to the line edit
    ui->commandLE->setFocus();
}

