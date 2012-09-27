#include "connecttoserverdialog.h"
#include "ui_connecttoserverdialog.h"

ConnectToServerDialog::ConnectToServerDialog(QHostAddress currentAddress, quint16 currentPort, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectToServerDialog)
{
    ui->setupUi(this);

    setupContraints();
}

ConnectToServerDialog::~ConnectToServerDialog()
{
    delete ui;
}

void ConnectToServerDialog::setupContraints()
{
    //IP spinbox contraints
    ui->ipByte1SP->setMaximum( 255 );
    ui->ipByte2SP->setMaximum( 255 );
    ui->ipByte3SP->setMaximum( 255 );
    ui->ipByte4SP->setMaximum( 255 );

    ui->ipByte1SP->setMinimum( 0 );
    ui->ipByte2SP->setMinimum( 0 );
    ui->ipByte3SP->setMinimum( 0 );
    ui->ipByte4SP->setMinimum( 0 );

    ui->ipByte1SP->setValue( 127 );
    ui->ipByte2SP->setValue( 0 );
    ui->ipByte3SP->setValue( 0 );
    ui->ipByte4SP->setValue( 1 );

    //Por constraints
    ui->portSP->setMinimum( 0 );
    ui->portSP->setMaximum( 65535 );
    ui->portSP->setValue( 7755 );
}

void ConnectToServerDialog::on_buttonBox_accepted()
{
    QString addressString;

    addressString.append( QString::number( ui->ipByte1SP->value() ) + "." );
    addressString.append( QString::number( ui->ipByte2SP->value() ) + "." );
    addressString.append( QString::number( ui->ipByte3SP->value() ) + "." );
    addressString.append( QString::number( ui->ipByte4SP->value() ) );

    QHostAddress address;
    address.setAddress( addressString );

    emit connectToServer( address, (quint16) ui->portSP->value() );
}

void ConnectToServerDialog::on_buttonBox_rejected()
{
    this->~ConnectToServerDialog();
}
