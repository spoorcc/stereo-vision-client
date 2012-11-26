#ifndef BOOLEANPARAMETER_H
#define BOOLEANPARAMETER_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  This class extends he abstract class with specific numeric methods and member variables

*/

//Local incluudes
#include "abstractparameter.h"

class BooleanParameter : public AbstractParameter
{
public:
    BooleanParameter(QString name, bool state = false);

    bool isBoolean() const;

    //Get methods
    bool isEnabled() const;
    bool isDisabled() const;

public slots:
    //Set methods
    void setEnabled();
    void setDisabled();
    void set( bool state );
    void toggle();

    void update(AbstractParameter *parameter);

private:
    bool _init;
    bool _state;
};

#endif // BOOLEANPARAMETER_H
