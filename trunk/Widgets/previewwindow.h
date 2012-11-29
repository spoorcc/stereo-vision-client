#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMenu>
#include <QVariant>

#include "previewchannel.h"

#define HORCHANNELCOUNT 4
#define VERCHANNELCOUNT 2

#define CHANNELWIDTH    640
#define CHANNELHEIGTH   480

namespace Ui {
class PreviewWindow;
}

class PreviewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewWindow(QWidget *parent = 0);
    ~PreviewWindow();

    void resizeEvent(QResizeEvent *);

signals:
    void requestPreviewStream( int previewChannel, QString procesStep, QString streamName, bool continous);

public slots:
    void addPreviewStream( QString processStep, QString streamName);
    void zoomToNumberOfChannels(int number);

private slots:
    void on_modeCB_currentIndexChanged(int index);

private:
    void disableScrollBars();

    void initChannelCountBox();
    void initPreviewScene();
    void initPreviewChannels();
    void initMenuBar();

    void selectChannels(QList<int> channelIDs);

    Ui::PreviewWindow *ui;
    QGraphicsScene* _previewScene;

    QList< PreviewChannel* > _previewChannels;
};

#endif // PREVIEWWINDOW_H
