#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class PreviewWindow;
}

class PreviewWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit PreviewWindow(QWidget *parent = 0);
    ~PreviewWindow();
    
private:
    Ui::PreviewWindow *ui;
    QGraphicsScene* _scene;
};

#endif // PREVIEWWINDOW_H
