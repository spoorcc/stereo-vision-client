#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QObject>
#include <QStringList>

class CommandLineParser : public QObject
{
    Q_OBJECT
public:
    explicit CommandLineParser(QObject *parent = 0);
    

signals:

    void commandParseError( QString errorMessage );

    void commandGUI( QString command );
    void parameterForServer( QString processStep, QString parameter, QString value );

public slots:
    void parseCommand( QString command );

private slots:
    bool isGuiCommand(QString command);
};

#endif // COMMANDLINEPARSER_H
