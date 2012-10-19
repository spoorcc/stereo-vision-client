#include "commandlineparser.h"

CommandLineParser::CommandLineParser(QObject *parent) :
    QObject(parent)
{
}

void CommandLineParser::parseCommand(QString command)
{
    QStringList commandParts = command.split(" ");

    if (QString::compare( commandParts.at(0), "Preview",Qt::CaseInsensitive) == 0 )
    {

    }

    if( QString::compare( commandParts.at(0), "Set", Qt::CaseInsensitive) == 0 )
    {
        if( commandParts.count() == 4)
        {
            emit lastCommand(" Setting " + commandParts.at(2) + " of processStep " + commandParts.at(1) + " to a value of " + commandParts.at(3) , true);
            return;
        }
        else
        {
            emit lastCommand("Error parsing command:  <br>Command should be structured like following:<br> Set &lt;processStep&gt; &lt;parameter&gt; &lt;value&gt;",false);
        }
    }

    if (QString::compare( commandParts.at(0), "save",Qt::CaseInsensitive) == 0 )
    {
        if (QString::compare( commandParts.at(1), "preview",Qt::CaseInsensitive) == 0 )
        {
            emit lastCommand("Preview Saved", true);
            return;
        }
        if (QString::compare( commandParts.at(1), "log",Qt::CaseInsensitive) == 0 )
        {
            emit lastCommand("Log Saved", true);
            return;
        }
        else
        {
            emit lastCommand("Error parsing command: <br>Save must always be followed by either &quot;preview&quot; or &quot;log&quot;" ,false);
        }
    }
    emit lastCommand(command,false);
}
