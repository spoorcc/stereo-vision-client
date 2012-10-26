#ifndef COMMANDLINEWIDGET_H
#define COMMANDLINEWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QKeyEvent>

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
    void setOldCommand();
    void addCommandToHistory();

private:

    int _commandIndex;
    QStringList _commandHistory;
    Ui::CommandLineWidget *ui;

    bool eventFilter(QObject *obj, QEvent *event);
    void focusInEvent(QFocusEvent *);
};

#endif // COMMANDLINEWIDGET_H
