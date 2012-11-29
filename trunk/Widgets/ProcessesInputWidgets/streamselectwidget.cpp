#include "streamselectwidget.h"
#include "ui_streamselectwidget.h"


StreamSelectWidget::StreamSelectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StreamSelectWidget)
{
    ui->setupUi(this);

}

StreamSelectWidget::~StreamSelectWidget()
{
    delete ui;
}

void StreamSelectWidget::setStreams(QStringList streams)
{
    foreach( QString stream,streams)
    {
        addDropdown(stream);
    }
    addSpacer();
}

void StreamSelectWidget::addDropdown(QString name)
{
    //Create a combobox
    QComboBox* comboBox = new QComboBox(this);
    comboBox->addItem(name);
    comboBox->addItem("Preview");
    comboBox->addItem("Replace");
    ui->horizontalLayout->addWidget( comboBox );

}

void StreamSelectWidget::addSpacer()
{
    //For better layout, create a spacer
    QSpacerItem* horizontalSpacer = new QSpacerItem (10,10, QSizePolicy::Expanding);
    ui->horizontalLayout->addSpacerItem(horizontalSpacer);
}

void StreamSelectWidget::setAsInput()
{
    ui->nameLBL->setText("Input");
}

void StreamSelectWidget::setAsOutput()
{
    ui->nameLBL->setText("Output");
}
