#include "commandlineparser.h"

CommandLineParser::CommandLineParser(QObject *parent) :
    QObject(parent)
{
}

void CommandLineParser::parseCommand(QString command)
{
    QStringList commandParts = command.split(" ");

    if( commandParts.count() != 3)
    {
        emit commandParseError( "\n\n Error parsing command:  \n Command should be structured like following: <processStep> <parameter> <value>" );
        return;
    }
    else
    {
        emit commandParseSucces(" Setting " + commandParts.at(1) + " of processStep " + commandParts.at(0) + " to a value of " + commandParts.at(2) );
        return;
    }

}
