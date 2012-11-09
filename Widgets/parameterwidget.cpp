#include "parameterwidget.h"
#include "ui_parameterwidget.h"

ParameterWidget::ParameterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterWidget)
{
    ui->setupUi(this);
    _type = UNKWOWN;
}

ParameterWidget::~ParameterWidget()
{
    delete ui;
}

void ParameterWidget::setParameter(AbstractParameter *parameter)
{
    ui->nameLBL->setToolTip( parameter->description() );
    if( parameter->isBoolean() )
    {
        createBooleanWidget( parameter );
    }
    if( parameter->isNumerical() )
    {
        createNumericWidget( parameter );
    }
    if( parameter->isSelect() )
    {
        createSelectWidget( parameter );
    }
}

void ParameterWidget::setValue(QString value)
{
    //FInd type
    qDebug() << ui->nameLBL->text() << "Updating value to " << value;

    switch( _type )
    {
    case BOOLEAN:
        setBooleanValue( value );
        break;
    case NUMERICAL:
        setNumericalValue( value );
        break;
    case SELECTABLE:
        setSelectableValue( value );
        break;
    default:
        break;
    }
}
void ParameterWidget::setBooleanValue( QString value )
{

    QList< QObject* > allCheckBoxes = ui->parameterLO->children();
    //QCheckBox* checkBox = ui->horizontalLayout->findChild< QCheckBox* >("booleanParameter");
    QCheckBox* checkBox = (QCheckBox*) ui->horizontalLayout->children().last();

    if( checkBox == 0 )
    {
        return;
    }

    QStringList validSetStatements;
    validSetStatements.append("true");
    validSetStatements.append("enable");
    validSetStatements.append("check");

    foreach( QString statement, validSetStatements )
    {
        if( QString::compare( statement, value, Qt::CaseInsensitive ) == 0 )
        {
            checkBox->setChecked( true );
        }
    }

    QStringList validUnSetStatements;
    validUnSetStatements.append("false");
    validUnSetStatements.append("disable");
    validUnSetStatements.append("uncheck");

    foreach( QString statement, validUnSetStatements )
    {
        if( QString::compare( statement, value, Qt::CaseInsensitive ) == 0 )
        {
            checkBox->setChecked( false );
        }
    }

    checkBox->update();
}
void ParameterWidget::setNumericalValue( QString value )
{

}
void ParameterWidget::setSelectableValue( QString value )
{

}

void ParameterWidget::createBooleanWidget(AbstractParameter *parameter)
{
    _type = BOOLEAN;

    // Set the name of the parameter
    ui->nameLBL->setText( ((BooleanParameter*) parameter)->name() );

    //Create a checkbox and add one
    QCheckBox* checkBox = new QCheckBox (this);
    checkBox->setObjectName("booleanParameter");
    checkBox->setChecked( ((BooleanParameter*) parameter)->isEnabled() );
    ui->parameterLO->addWidget(checkBox);

    addSpacer();
}

void ParameterWidget::createNumericWidget(AbstractParameter *parameter)
{
    _type = NUMERICAL;

    ui->nameLBL->setText( ((NumericParameter*) parameter)->name() );

    //Create a spinbox

    QSpinBox* spinBox = new QSpinBox(this);
    spinBox->setObjectName("numericParameter");
    spinBox->setMaximum( ((NumericParameter*)parameter)->maximum() );
    spinBox->setMinimum( ((NumericParameter*)parameter)->minimum() );
    spinBox->setValue( ((NumericParameter*)parameter)->init());
    ui->parameterLO->addWidget(spinBox);

    addSpacer();
}
void ParameterWidget::createSelectWidget( AbstractParameter *parameter)
{
    _type = SELECTABLE;

    ui->nameLBL->setText( ( (SelectParameter*) parameter)->name() );

    //Create a combobox
    QComboBox* comboBox = new QComboBox(this);
    comboBox->setObjectName("selectableParameter");
    comboBox->setToolTip( parameter->description() );

    for( int i = 0; i < ((SelectParameter*) parameter)->count(); i++ )
    {
        comboBox->addItem( ((SelectParameter*) parameter)->option(i) );
    }

    ui->parameterLO->addWidget( comboBox );

    addSpacer();
}
void ParameterWidget::addSpacer()
{
    //For better layout, create a spacer
    QSpacerItem* horizontalSpacer = new QSpacerItem (10,10, QSizePolicy::Expanding);
    ui->parameterLO->addSpacerItem(horizontalSpacer);
}

