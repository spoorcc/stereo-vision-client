#include "selectparameter.h"

SelectParameter::SelectParameter( QString name )
{
    _selectedOption = -1;
    setName( name );
}
int SelectParameter::count()
{
    return _options.count();
}

bool SelectParameter::isSelect() const
{
    return true;
}

QString SelectParameter::option(int index)
{
    return _options.at( index );
}

QString SelectParameter::giveSelectedOption()
{
    return _options.at( _selectedOption );
}

void SelectParameter::addOption(QString name)
{
    _options.append( name );

    if( count() == 1 )
    {
        _selectedOption = 0;
    }
}
void SelectParameter::removeOption( int index )
{
    _options.removeAt( index );

    if( count() == 0 )
    {
        _selectedOption = -1;
    }
    if( _selectedOption >= count() )
    {
        _selectedOption = count() - 1;
    }
}

void SelectParameter::selectOption(int index)
{
    if( index < 0 )
    {
        emit illegalUpdate();
        return;
    }
    if( index >= count() )
    {
        emit illegalUpdate();
        return;
    }

    _selectedOption = index;
}

void SelectParameter::update(AbstractParameter *parameter)
{
    if( !( parameter->isSelect() ) )
    {
        emit illegalUpdate();
        return;
    }
    else
    {
        _options.clear();

        for( int i = 0; i < ((SelectParameter*) parameter)->count(); i++ )
        {
            _options.append( ((SelectParameter*) parameter)->option(i) );
        }
    }
}
