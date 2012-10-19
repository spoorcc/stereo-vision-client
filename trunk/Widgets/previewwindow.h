#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QDebug>

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsProxyWidget>
#include <QComboBox>

#include "singlepreviewchannelitem.h"

namespace Ui {
class PreviewWindow;
}

class PreviewWindow : public QWidget
{
    Q_OBJECT

    enum Mode { singleView, dualView, quadView, octoView, configMode};
    
public:
    explicit PreviewWindow(QWidget *parent = 0);
    ~PreviewWindow();

    void addVideoStream( QString streamName );

private slots:
    void on_configPB_clicked();

private:
    Ui::PreviewWindow *ui;
    QGraphicsScene* _scene;

    PreviewWindow::Mode _mode;

    QList< SinglePreviewChannelItem* > _previewChannels;
    QList< QComboBox* > _videoStreamCB;

    int _numberOfWindows;

    void addImage(QPixmap image);
    void clearAll();
    void createScene();

    void drawConfigScreen();

    void drawSingleView();
    void drawDualView();
    void drawQuadView();
    void drawOctoView();

    void makeChannelsUnvisible(int index);

    void scaleForMode(PreviewWindow::Mode previous, PreviewWindow::Mode next);
};

#endif // PREVIEWWINDOW_H
