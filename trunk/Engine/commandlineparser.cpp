#include "commandlineparser.h"

CommandLineParser::CommandLineParser(QObject *parent) :
    QObject(parent)
{
}

void CommandLineParser::parseCommand(QString command)
{
    if( isGuiCommand(command) )
    {
        emit commandGUI( command );
        return;
    }

    QStringList commandParts = command.split(" ");

    if( commandParts.count() != 3)
    {
        emit commandParseError( "\n\n Error parsing command:  \n Command should be structured like following: <processStep> <parameter> <value>" );
        return;
    }



}
bool CommandLineParser::isGuiCommand( QString command )
{
    return false;
}
