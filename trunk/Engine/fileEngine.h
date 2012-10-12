#ifndef FILEENGINE_H
#define FILEENGINE_H

#include <QObject>

class fileEngine : public QObject
{
    Q_OBJECT
public:
    explicit fileEngine(QObject *parent = 0);
    void saveFile(QString destination, QString type);
    void openFile(QString destination);
signals:
    
public slots:
    
};

#endif // FILEENGINE_H
