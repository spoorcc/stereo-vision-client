#ifndef PROCESSSTEP_H
#define PROCESSSTEP_H

#include <QWidget>

namespace Ui {
class ProcessStep;
}

class ProcessStep : public QWidget
{
    Q_OBJECT
    
public:
    explicit ProcessStep(QWidget *parent = 0);
    ~ProcessStep();

    void setName(QString name);
    
private:
    Ui::ProcessStep *ui;
};

#endif // PROCESSSTEP_H
