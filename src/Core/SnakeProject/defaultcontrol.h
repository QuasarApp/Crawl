#ifndef DEFAULTCONTROL_H
#define DEFAULTCONTROL_H

#include "icontrol.h"

/**
 * @brief The DefaultControl class This class contains default implementation of the game menu.
 */
class DefaultControl : public IControl
{
public:
    DefaultControl();

    // IControl interface
public:
    QString initQmlView() const;
};

#endif // DEFAULTCONTROL_H
