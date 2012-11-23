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
    void saveLog();

    void sendCommandToServer( QString command );
    void set( QString processStep, QString parameter, QString value);

    void printToConsole( QString sender, QString message );

    void commandForGui( QString command );
    
private slots:
    void on_commandPB_clicked();

    void sendCommand();
    void setOldCommand();
    void addCommandToHistory();

    void parseCommand();

    QString lastCommand();

    bool equals(QString string1, QString string2, Qt::CaseSensitivity sensitivity = Qt::CaseInsensitive);
    bool firstPartIs(QString command);

    void commandParseStatus(QString message, bool succesfull);

private:

    int _commandIndex;
    QStringList _commandHistory;
    Ui::CommandLineWidget *ui;

    QStringList splitCommandInArguments(QString command);

    bool eventFilter(QObject *obj, QEvent *event);
    void focusInEvent(QFocusEvent *);
};

#endif // COMMANDLINEWIDGET_H
