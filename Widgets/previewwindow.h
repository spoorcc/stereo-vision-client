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
    
    void displayTwoImages(QPixmap image, QPixmap image2);
private:
    Ui::PreviewWindow *ui;
    QGraphicsScene* _scene;

    void addImage(QPixmap image);
    void clearAll();
};

#endif // PREVIEWWINDOW_H
