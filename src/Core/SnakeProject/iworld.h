#ifndef IWORLD_H
#define IWORLD_H

#include "iplayer.h"

#include <QHash>
#include <QMap>
#include <QMultiHash>
#include <QObject>
#include <QString>
#include "irender.h"

class IWorldItem;
class IPlayer;

/**
 * @brief WorldObjects This is map list of the avalable objects and its count on a lvl-long point.
 */
typedef QMap<QString, int> WorldObjects;

/**
 * @brief WorldRule This is list of the lvl-long points and its rules. For get more information see the WorldOBjects typedef.
 */
typedef QMap<int, WorldObjects> WorldRule;

/**
 * @brief The WorldObjectWraper struct This is simple wraper structure for the internal functionality of the IWorld objects.
 */
struct WorldObjectWraper {
    IWorldItem* objectPtr = nullptr;
    QString groupName = "";
};

/**
 * @brief The IWorld class use this interface for implementation your own game levels
 */
class IWorld : public QObject, public IRender
{
    Q_OBJECT
public:
    IWorld();
    virtual ~IWorld();

    /**
     * @brief initPlayer The implementation of This interface must be return playerObject.
     * @return raw pointer to the player object.
     * @note The Palyer object will be deleted when wold distroed.
     *  So do not delete your created player pbject yuorself.
     */
    virtual IPlayer* initPlayer() const = 0;

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

    /**
     * @brief description This method shold be return lvl description.
     * @return lvel description string.
     */
    virtual QString description() const = 0;

    /**
     * @brief imagePreview This method should be return path to banner of the lvl.
     * @return path to level banner.
     */
    virtual QString imagePreview() const = 0;

    /**
     * @brief name This method shold be return lvl name.
     * @return lvl name.
     */
    virtual QString name() const = 0;

    /**
     * @brief costToUnlock This method shold be return unlock cost.
     * @return unlock cost
     */
    virtual int costToUnlock() const = 0;

    /**
     * @brief render this method recursive invoke all render functions of the all world items.
     *  The render function is main function of the SnakeEngine This method recal all propertyes of all objects.
     */
    virtual void render(unsigned int tbfMsec) override;

    /**
     * @brief getItem This method return raw pointer to object by id.
     * @param id This is id of a required object.
     * @return pointe to requaried object.
     * @note if you want to get ovject in the render function of another ItemWorld object then use the IWorldItem::getItem method.
     */
    const IWorldItem * getItem(int id) const;

    const QString &hdrMap() const;

signals:
    void sigGameFinished(GameResult);

protected:
    /**
     * @brief generate This method shold be generate object from the  @a objectType.
     *  Override this method for add support yourown objects.
     * @param objectType This is string type name of the object,
     * @return pointer to the object.
     */
    virtual IWorldItem* generate(const QString& objectType) const = 0;

private:
    bool init();
    void deinit();

    void worldChanged(const WorldObjects& objects);
    void clearItems();
    void addItem(const QString &group, IWorldItem *obj);
    bool removeItem(int id);
    bool removeAnyItemFromGroup(const QString &group);

    QHash<int, WorldObjectWraper> _items;
    QMultiHash<QString, int> _itemsGroup;

    QString _hdrMap;
    WorldRule *_worldRules = nullptr;
    IPlayer *_player = nullptr;

    friend class Engine;

};

#endif // IWORLD_H
