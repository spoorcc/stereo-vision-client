#include "connecttoserverdialog.h"
#include "ui_connecttoserverdialog.h"

ConnectToServerDialog::ConnectToServerDialog(QHostAddress currentAddress, quint16 currentPort, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectToServerDialog)
{
    ui->setupUi(this);

    setupContraints();
    setAddress( currentAddress);
    setPort( currentPort );
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

    //Port constraints
    ui->portSP->setMinimum( 0 );
    ui->portSP->setMaximum( 65535 );

}
void ConnectToServerDialog::setAddress( QHostAddress address )
{
    QString addressString = address.toString();
    QStringList addressParts = addressString.split(".");

    ui->ipByte1SP->setValue( addressParts.at(0).toInt() );
    ui->ipByte2SP->setValue( addressParts.at(1).toInt() );
    ui->ipByte3SP->setValue( addressParts.at(2).toInt() );
    ui->ipByte4SP->setValue( addressParts.at(3).toInt() );
}

void ConnectToServerDialog::setPort(quint16 port)
{
    ui->portSP->setValue( port );
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
