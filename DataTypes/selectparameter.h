#ifndef SELECTPARAMETER_H
#define SELECTPARAMETER_H

#include "abstractparameter.h"

class SelectParameter : public AbstractParameter
{
public:
    SelectParameter(QString name);
    int count();

    bool isSelect() const;
    QString option( int index );
    QString giveSelectedOption();

public slots:
    void addOption( QString name );
    void removeOption( int index );

    void selectOption( int index );

    void update(AbstractParameter *parameter);

private:
    QList< QString > _options;
    int _selectedOption;
};

#endif // SELECTPARAMETER_H
