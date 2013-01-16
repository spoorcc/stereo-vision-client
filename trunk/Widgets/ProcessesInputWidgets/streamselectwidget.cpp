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
        addStream(stream);
    }
    addSpacer();
}
void StreamSelectWidget::addStream( QString stream )
{
    //Create downarrow label
    QLabel* arrowLbl = new QLabel(this);
    QPixmap* arrowPixmap = new QPixmap(":/Icons/down_arrow");
    arrowLbl->setPixmap( *arrowPixmap);
    ui->horizontalLayout->addWidget( arrowLbl );

    //Add text
    QLabel* textLabel = new QLabel(this);
    textLabel->setTextFormat(Qt::RichText);
    textLabel->setText( "|<i>" +  stream +  "</i>|" );
    ui->horizontalLayout->addWidget( textLabel );
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
    ui->nameLBL->setTextFormat(Qt::RichText);
    ui->nameLBL->setText("<b>Inputs</b>");
}

void StreamSelectWidget::setAsOutput()
{
    ui->nameLBL->setTextFormat(Qt::RichText);
    ui->nameLBL->setText("<b>Outputs</b>");
}
