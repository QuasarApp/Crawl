#ifndef IWORLD_H
#define IWORLD_H

#include "isnake.h"

#include <QMap>
#include <QString>

class ItemWorld;

/**
 * @brief WorldRules
 * this map conteins:
 * 1. list of generated objects and they count.
 * 2. long of world (Long),
 * 3. spead of world (Spead),
 * !!!Note: all object show on map alltime.
 */

/**
 * @brief WorldObjects This is map list of the avalable objects and its count on a lvl-long point.
 */
typedef QMap<QString, int> WorldObjects;

/**
 * @brief WorldRule This is list of the lvl-long points and its rules. For get more information see the WorldOBjects typedef.
 */
typedef QMap<int, WorldObjects> WorldRule;

/**
 * @brief The IWorld class use this interface for implementation your own game levels
 */
class IWorld
{
public:
    IWorld();
    virtual ~IWorld();

    /**
     * @brief initPlayer The implementation of This interface must be return playerObject.
     * @return raw pointer to the player object.
     * @note The Palyer object will be deleted when wold distroed.
     *  So do not delete your created player pbject yuorself.
     */
    virtual ISnake* initPlayer() const = 0;

    /**
     * @brief initWorldRules The implementation of this interface must be retun initialized list of the world rules.
     *  For more information see the WorldRules map.
     * @return a raw pointer to world a rules map.
     * @note The Palyer object will be deleted when wold distroed.
     *  So do not delete your created player pbject yuorself.
     */
    virtual WorldRule* initWorldRules() const = 0;

    /**
     * @brief initHdrBackGround The implementation of this method must be return valid path to the hdr image map.
     * The hdr image map it is background jpeg image.
     * @return path to hfr map.
     */
    virtual QString initHdrBackGround() const = 0;

private:

    bool init();

    void deinit();

    ISnake * _snake;
    QMap<QString, ItemWorld*> items;

    int endLong;
    float spead = 0, d_spead = 0, currentLong = 0;
    QString _hdrMap;
    WorldRule *_worldRules = nullptr;

    friend class Engine;
};

#endif // IWORLD_H
