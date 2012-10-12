#ifndef STREAMSELECTWIDGET_H
#define STREAMSELECTWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QStringList>


namespace Ui {
class StreamSelectWidget;
}

class StreamSelectWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit StreamSelectWidget(QWidget *parent = 0);
    ~StreamSelectWidget();
    

    void setStreams(QStringList streams);

    void setAsInput();
    void setAsOutput();
private:
    Ui::StreamSelectWidget *ui;
    void addDropdown(QString name);
    void addSpacer();
};

#endif // STREAMSELECTWIDGET_H
