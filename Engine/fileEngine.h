#ifndef FILEENGINE_H
#define FILEENGINE_H

#define MAXLOGENTRIES 10000

#include <QObject>
#include <QStringlist>
#include <QTextStream>
#include <QDesktopServices>
#include <QFile>
#include <QDir>
#include <QTime>

class FileEngine : public QObject
{
    Q_OBJECT
public:
    explicit FileEngine(QObject *parent = 0);

signals:
    void logSaved(QString destination);

public slots:
    void openFile(QString destination);
    void setDestination(QString destination);
    void makeEntry(QString entry);
    void saveLog();

private:
    QString _destination;
    QString _fileName;
    QString _fileExtension;
    QStringList _log;
    void checkForOverload();
    QString timeStamp();
};

#endif // FILEENGINE_H
