#ifndef DEFAULTCONTROL_H
#define DEFAULTCONTROL_H

#include "icontrol.h"

/**
 * @brief The DefaultControl class This class contains default implementation of the game menu.
 */
class DefaultControl : public IControl {
    Q_OBJECT
public:
    DefaultControl();

    /**
     * @brief initQmlView This implementation use the DefaultMenu.qml file.
     * @return qrc:/SnakeProjectModule/DefaultMenu.qml
     */
    QString initQmlView() const;

signals:
    void backToMenu();
};

#endif // DEFAULTCONTROL_H
