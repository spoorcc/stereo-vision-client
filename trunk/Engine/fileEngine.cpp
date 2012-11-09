#include "fileEngine.h"

FileEngine::FileEngine(QObject *parent) :
    QObject(parent)
{
    _destination = QDesktopServices::ApplicationsLocation+ "\\StereoVisionLog\\";
    _fileName = "Log";
    _fileExtension ="html";
}

void FileEngine::openFile(QString destination)
{
   // QFile::open()
}

void FileEngine::setDestination(QString destination)
{
        _destination = destination;
}

void FileEngine::makeEntry(QString entry)
{
    _log.append( entry );
    checkForOverload();
}

void FileEngine::saveLog()
{
    QDir::setCurrent( _destination);
    QString fileName = ( _fileName + timeStamp() + "." + _fileExtension );
    QFile file( fileName );

     emit printToConsole("Interface", "Trying to save log in: " + _destination + " with name: " + fileName +  " and clear memory");

    if (file.open(QFile::WriteOnly | QFile::Truncate ))
     {
         QTextStream out(&file);
         out << "<html>";
         foreach( QString logLine, _log )
         {
             out << logLine + "<br>";
         }
         out << "<//html>";
         out.flush();
         _log.clear();
         emit printToConsole("Interface", "Saved log in: " + _destination + " with name: " + fileName +  " and cleared memory");
     }
    else
    {
        emit printToConsole("Interface", "Couldn't save log in: " + _destination + " with name: " + fileName +  " and clear memory");
    }
     file.close();
}

void FileEngine::checkForOverload()
{
    if (_log.count() > MAXLOGENTRIES)
    {
        saveLog();
        for (int i = MAXLOGENTRIES; i > 0; i-- )
        {
            _log.removeFirst();
        }
    }
}

QString FileEngine::timeStamp()
{
    return QString(QDate::currentDate().toString( "yyMMdd" ) + "ed" + QTime::currentTime().toString( "hhmmss" ));
}
