#include "fileEngine.h"

FileEngine::FileEngine(QObject *parent) :
    QObject(parent)
{
    _destination = QDesktopServices::storageLocation( QDesktopServices::DocumentsLocation );
    _fileName = "Log";
    _fileExtension ="txt";
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
    QDir::setCurrent( _destination );
    QString fileName = ( _fileName + timeStamp() + "." + _fileExtension );
    QFile file( fileName );
     if (file.open(QFile::WriteOnly | QFile::Truncate))
     {
         QTextStream out(&file);
         foreach( QString logLine, _log )
         {
            out << logLine;
         }
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
    return QString(QDate::currentDate().toString("yyMMdd") + "@" + QTime::currentTime().toString("hh:mm:ss"));
}
