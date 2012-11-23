#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QObject>
#include <QStringList>
#include <QDir>

class CommandLineParser : public QObject
{
    Q_OBJECT
public:
    explicit CommandLineParser(QObject *parent = 0);    

signals:

    void lastCommand(QString command, bool succesfull);
    void sendCommandToServer( QString command );

public slots:
    void parseCommand( QString command );

};

#endif // COMMANDLINEPARSER_H
