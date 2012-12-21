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
    if( parameter->isPerform() )
    {
        createPerformWidget( parameter );
    }
}

void ParameterWidget::setValue(QString value)
{
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
    case PERFORM:
        setPerformValue( value );
        break;
    default:
        illegalUpdate( "Parameter widget is of unknown type");
        break;
    }
}
void ParameterWidget::setBooleanValue( QString value )
{
    QCheckBox* checkBox = findChild< QCheckBox* >("booleanParameter");

    if( checkBox == 0 )
    {
        emit illegalUpdate( "No checkbox was found to set");
        return;
    }

    QStringList validSetStatements;
    validSetStatements << "true" << "enable" << "check" << "enabled" << "1" << "t";

    foreach( QString statement, validSetStatements )
    {
        if( QString::compare( statement, value, Qt::CaseInsensitive ) == 0 )
        {
            if( !checkBox->isChecked() )
            {
                checkBox->setChecked( true );
                emit valueChanged( ui->nameLBL->text(), "true");
            }
            return;
        }
    }

    QStringList validUnSetStatements;
    validUnSetStatements << "false" << "disable" << "disabled" << "uncheck" << "0" << "f";

    foreach( QString statement, validUnSetStatements )
    {
        if( QString::compare( statement, value, Qt::CaseInsensitive ) == 0 )
        {
            if( checkBox->isChecked() )
            {
                checkBox->setChecked( false );
                emit valueChanged( ui->nameLBL->text(), "false");
            }
            return;
        }
    }

    emit illegalUpdate( value + " is not a valid (un)set statement" );
    //checkBox->update();
}
void ParameterWidget::setNumericalValue( QString value )
{
    QSpinBox* spinBox = findChild< QSpinBox* >("numericParameter");

    if( spinBox == 0)
    {
        return;
    }

    int newValue = value.toInt();

    if( newValue >= spinBox->minimum() && newValue <= spinBox->maximum()  )
    {
        if(newValue != spinBox->value() )
        {
            spinBox->setValue( newValue );
            emit valueChanged( ui->nameLBL->text(), value);
        }
    }
    else
    {
        emit illegalUpdate( QString("Value: %1 is out of range [ %2 -> %3 ]").arg(newValue).arg(spinBox->minimum()).arg( spinBox->maximum() ) );
    }

    spinBox->update();

}
void ParameterWidget::setSelectableValue( QString value )
{
    QComboBox* comboBox = findChild< QComboBox* >("selectableParameter");

    if( comboBox == 0)
    {
        emit illegalUpdate( "No combobox was found");
        return;
    }
    int index = comboBox->findText( value );

    if( index == -1 )
    {
        emit illegalUpdate( "Option \""+value+"\" is not found");
        return;
    }
    else if(index != comboBox->currentIndex() )
    {
        comboBox->setCurrentIndex( index );
        emit valueChanged( ui->nameLBL->text(), value);
    }

    comboBox->update();
}

void ParameterWidget::setPerformValue(QString value)
{
    QPushButton* button = findChild< QPushButton* >("performParameter");

    if( button == 0 )
    {
        emit illegalUpdate( "No perform parameter / button was found to trigger");
        return;
    }

    QStringList validSetStatements;
    validSetStatements << "true" << "enable" << "check" << "enabled" << "1" << "t" << "go" << "fire" << "execute" << "perform";

    foreach( QString statement, validSetStatements )
    {
        if( QString::compare( statement, value, Qt::CaseInsensitive ) == 0 )
        {
            emit valueChanged( ui->nameLBL->text(), "perform");
            return;
        }
    }
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

void ParameterWidget::createPerformWidget(AbstractParameter *parameter)
{
    _type = PERFORM;

    ui->nameLBL->setText( "" );

    QPushButton* button = new QPushButton(this);
    button->setObjectName("performParameter");
    button->setToolTip( parameter->description() );
    button->setText(  ((PerformParameter*) parameter)->name() );

    ui->parameterLO->addWidget( button );

    addSpacer();
}
void ParameterWidget::addSpacer()
{
    //For better layout, create a spacer
    QSpacerItem* horizontalSpacer = new QSpacerItem (10,10, QSizePolicy::Expanding);
    ui->parameterLO->addSpacerItem(horizontalSpacer);
}

