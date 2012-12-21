#ifndef PERFORMPARAMETER_H
#define PERFORMPARAMETER_H

/*
  Project:      Stereo-vision-client
  Author:       Ben
  Description:  This class extends the abstract class and is a single shot button on the gui

*/

//Local incluudes
#include "abstractparameter.h"

class PerformParameter : public AbstractParameter
{
public:
    PerformParameter(QString name, bool fireOnInit);

    bool isPerform() const;

    bool fireOnInit();

public slots:

    //Set methods
    void perform();
    void setFireOnInit( QString value );

    void update(AbstractParameter *parameter);
private:
    bool _fireOnInit;


};

#endif // PERFORMPARAMETER_H
