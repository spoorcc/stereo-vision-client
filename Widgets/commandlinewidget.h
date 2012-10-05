#ifndef COMMANDLINEWIDGET_H
#define COMMANDLINEWIDGET_H

#include <QWidget>

namespace Ui {
class CommandLineWidget;
}

class CommandLineWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CommandLineWidget(QWidget *parent = 0);
    ~CommandLineWidget();

signals:
    void executeCommand( QString command);
    
private slots:
    void on_commandPB_clicked();

    void on_commandLE_returnPressed();

    void sendCommand();

private:
    Ui::CommandLineWidget *ui;
};

#endif // COMMANDLINEWIDGET_H
