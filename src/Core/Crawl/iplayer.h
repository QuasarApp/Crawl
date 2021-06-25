//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IPLAYER_H
#define IPLAYER_H

#include "gameresult.h"
#include "global.h"
#include "iworlditem.h"
#include "Extensions/movableobject.h"

class IControl;

/**
 * @brief The IPlayer class This is base class of the player functions.
 */
class CRAWL_EXPORT IPlayer: public IWorldItem, protected MovableObject {
    Q_OBJECT
public:
    IPlayer(const QString& name,
            const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
            QObject *ptr = nullptr);

    /**
     * @brief getCurrentStatus This method return current game state of the player.
     * @return current gameState.
     */
    GameResult getCurrentStatus() const;

    /**
     * @brief isDead This method return true if your player are dead.
     * @return true if a player are dead.
     */
    bool isDead() const;

    /**
     * @brief speed This method return current speed of the snake.
     * @return current speed
     */
    float speed() const;

    /**
     * @brief setSpeed This method sets new value for player spead.
     * @param newSpead This is a new value of a snake speed.
     */
    void setSpeed(float newSpead);

    /**
     * @brief setControl This method should be connect player object with control object.
     * @param control This is control object.
     * @note This method can invoked two or more times, for example connect with AI control object and player control object. So your implementation should be contains disconnect methods.
     */
    virtual void setControl(const IControl* control);

protected:

    /**
     * @brief kill This method kill your player.
     *  Invoke this method when you want to kell your player.
     */
    void kill();

    /**
     * @brief reward This method add reward for player.
     * @param value This is new value;
     * @note This method increment current value.
     */
    void reward(int value);

    /**
     * @brief speedUp This method increment snake speed.
     * @param increment This is value that will added to a snake speed.
     * @return new snake speed.
     */
    float speedUp(float increment);

    /**
     * @brief setSpeedDown This method decrement snake speed.
     * @param decrement This is value that will take away from a snake speed.
     * @return new snake speed.
     * @note return 0 if a snake speed less than a decrement value.
     */
    float setSpeedDown(float decrement);

    /**
     * @brief fine This method remove reward for player.
     * @param value This is fine amount;
     * @note This method decriment current points value.
     */
    void fine(int value);

    void render(unsigned int tbfMsec) override;

protected slots:
    /**
     * @brief onTap This method invoked when user tap on screen.
     * @note method connected in the IPlayer::setControl function. So if you overrid the IPlayer::setControl method then please invoke method of a parent class.
     */
    virtual void onTap() = 0;


private:
    bool _fDead = false;
    int _currentPoints = 0;
    float _speed = 0;
    const IControl * _currentControl = nullptr;

};

#endif // IPLAYER_H
