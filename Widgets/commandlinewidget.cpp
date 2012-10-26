#include "commandlinewidget.h"
#include "ui_commandlinewidget.h"

CommandLineWidget::CommandLineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandLineWidget)
{
    ui->setupUi(this);
    this->setFocusPolicy( Qt::StrongFocus );
    ui->commandLE->installEventFilter(this);
    _commandIndex = -1;

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
    if( _commandIndex < 0)
    {
        return;
    }
    if( _commandIndex >= _commandHistory.count())
    {
        return;
    }

    ui->commandLE->setText( _commandHistory.at( _commandIndex));
}
void CommandLineWidget::addCommandToHistory()
{
    //Check if command already exists
    QString newCommand = ui->commandLE->text();
    QString command;

    for(int i = 0; i < _commandHistory.count() ; i++ )
    {
        command = _commandHistory.at(i);
        if( newCommand == command)
        {
           _commandHistory.removeAt(i);
        }
    }

    _commandHistory.prepend( ui->commandLE->text() );

    if (_commandHistory.size()>100)
    {
        _commandHistory.pop_back();
    }
}

void CommandLineWidget::sendCommand()
{
    if (ui->commandLE->text().count() > 0)
    {
        emit executeCommand( ui->commandLE->text() );

        addCommandToHistory();

        ui->commandLE->clear();
    }

    _commandIndex = -1;
}
void CommandLineWidget::focusInEvent(QFocusEvent *)
{
    //If the commandline widget gets focus itgives focus to the line edit
    ui->commandLE->setFocus();
}

