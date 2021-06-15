#ifndef DEFAULTCONTROL_H
#define DEFAULTCONTROL_H

#include "icontrol.h"
#include "global.h"

/**
 * @brief The DefaultControl class This class contains default implementation of the game menu.
 */
class SNAKEPROJECT_EXPORT DefaultControl : public IControl {
    Q_OBJECT
public:
    DefaultControl();

    /**
     * @brief initQmlView This implementation use the DefaultMenu.qml file.
     * @return qrc:/SnakeProjectModule/DefaultMenu.qml
     */
    QString initQmlView() const;

signals:
    /**
     * @brief backToMenu Emit when user click the return to main menu button.
     */
    void backToMenu();

    /**
     * @brief userTap Emit when user tap to screen on any position.
     */
    void userTap();
};

#endif // DEFAULTCONTROL_H
