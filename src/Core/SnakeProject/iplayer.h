#ifndef IPLAYER_H
#define IPLAYER_H

#include "gameresult.h"
#include "iworlditem.h"

/**
 * @brief The IPlayer class This is base class of the player functions.
 */
class IPlayer: public IWorldItem
{
    Q_OBJECT
public:
    IPlayer();

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

protected:
    /**
     * @brief kill This method kill your player. Invoke this method when you want to kell your player.
     */
    void kill();

    /**
     * @brief reward This method add reward for player.
     * @param value This is new value;
     * @note This method increment current value.
     */
    void reward(int value);

    /**
     * @brief fine This method remove reward for player.
     * @param value This is fine amount;
     * @note This method decriment current points value.
     */
    void fine(int value);

private:
    bool _fDead = false;
    int _currentPoints = 0;
};

#endif // IPLAYER_H
