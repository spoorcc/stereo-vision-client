#ifndef CONNECTTOSERVERDIALOG_H
#define CONNECTTOSERVERDIALOG_H

#include <QDialog>
#include <QHostAddress>

namespace Ui {
class ConnectToServerDialog;
}

class ConnectToServerDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConnectToServerDialog( QHostAddress currentAddress , quint16 currentPort, QWidget *parent = 0);
    ~ConnectToServerDialog();
    
signals:
    void connectToServer( QHostAddress adress, quint16 port );
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ConnectToServerDialog *ui;

    void setupContraints();
};

#endif // CONNECTTOSERVERDIALOG_H
