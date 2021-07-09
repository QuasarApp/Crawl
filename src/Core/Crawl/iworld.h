//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef CRAWL_IWORLD_H
#define CRAWL_IWORLD_H

#include "iplayer.h"

#include <QHash>
#include <QMap>
#include <QMultiHash>
#include <QObject>
#include <QQuaternion>
#include <QString>
#include "irender.h"
#include "global.h"
#include <QMutex>
#include "Crawl/diff.h"

class ClastersTest;

namespace CRAWL {

class IWorldItem;
class IPlayer;
class GroundClaster;
class IControl;
class IAI;

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
class CRAWL_EXPORT IWorld : public QObject, public IRender
{
    Q_OBJECT
    Q_PROPERTY(QVector3D cameraReleativePosition READ cameraReleativePosition NOTIFY cameraReleativePositionChanged)
    Q_PROPERTY(QQuaternion cameraRatation READ cameraRatation NOTIFY cameraRatationChanged)
    Q_PROPERTY(QObject * player READ player WRITE setPlayer NOTIFY playerChanged)
    Q_PROPERTY(QString hdr READ hdr NOTIFY hdrChanged)

    Q_PROPERTY(int worldStatus READ wordlStatus WRITE setWorldStatus NOTIFY worldStatusChanged)

public:
    IWorld();
    ~IWorld() override;

    void init() override;

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
     *
     *  Example of use :
     *
     *  ```cpp
     *  WorldRule *World::initWorldRules() {
     *      return new WorldRule {
     *            {
     *              0, {{registerObject<Box>(), 10}},
     *              100, {{registerObject<Box>(), 10}, {registerObject<Round>(), 1}},
     *            }
     *      };
     *  }
     *  ```
     *
     * @return a raw pointer to world a rules map.
     * @note The Palyer object will be deleted when wold distroed.
     *  So do not delete your created player pbject yuorself.
     *
     *
     */
    virtual WorldRule* initWorldRules() = 0;

    /**
     * @brief initUserInterface This method should be return point to userInterface object.
     * @note The base implementation return default user interface.
     * @return pointer to userInterface.
     */
    virtual IControl* initUserInterface() const;

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
     * @brief initPlayerControl This method should be configure all connections of @a control object.
     * @brief control This is control object
     * @note override this method if you have own IControl object.
     */
    virtual void initPlayerControl(IControl* control);

    /**
     * @brief start This method will be invoked when user click start button.
     * @note The Default implementation reset all positions for all objects.
     * @return true if game started successful.
     */
    virtual bool start();

    /**
     * @brief stop This methos will be invoked when user click to return to main menu button.
     * @note The default implementation sets new status of the world WordlStatus::Background.
     * @return true if aworld stoped successful
     */
    virtual bool stop();

    /**
     * @brief backGroundAI This method shuld be return pointer to control object for background AI.
     * @return raw pointer of backgroundAI.
     */
    virtual IAI *initBackGroundAI() const;

    /**
     * @brief getItem This method return raw pointer to object by id.
     * @param id This is id of a required object.
     * @return pointe to requaried object.
     * @note if you want to get ovject in the render function of another ItemWorld object then use the IWorldItem::getItem method.
     */
    IWorldItem *getItem(int id) const;

    /**
     * @brief cameraReleativePosition return  a releative of player camera position.
     * @return
     */
    const QVector3D &cameraReleativePosition() const;

    /**
     * @brief userInterface This method return pointer to userinterface.
     * @return pointer to user interface
     */
    IControl *userInterface() const;

    /**
     * @brief isInit This method return true if the object initialized correctly else false.
     * @return true if the object initialized correctly else false.
     */
    bool isInit() const;

    /**
     * @brief wordlStatus This method return current world status.
     * @return integer code of the status.
     */
    int wordlStatus() const;

    /**
     * @brief setWorldStatus This method sets new status of world.
     * @param newWorldStatus new status of world
     */
    void setWorldStatus(int newWorldStatus);

    /**
     * @brief backgroundAI This method return current backgroundAI.
     * @return Raw pointer to background AI object
     */
    IAI *backgroundAI() const;

    /**
     * @brief cameraRatation This method return curent camera ratation.
     * @return Quaternion of camera ratation
     */
    const QQuaternion &cameraRatation() const;

    /**
     * @brief player This method return player object
     * @return player object
     */
    QObject *player() const;

    /**
     * @brief hdr This method return path to hdr map of the lvl.
     * @return path to hdr map of this lvl.
     */
    const QString &hdr() const;

    /**
     * @brief runAsBackGround This method run this world as a backgroud.
     * The player start new game and sets new control from the backgroundAI method.
     */
    void runAsBackGround();

signals:
    /**
     * @brief sigGameFinished This signal emit when game are finished
     * @brief result This is player statistics after finished level,
     */
    void sigGameFinished(GameResult result);

    /**
     * @brief sigOBjctsListChanged This signal emited when lvel status are changed.
     * @brief diff This is list of removed and addeds items
     */
    void sigOBjctsListChanged(CRAWL::Diff diff);

    /**
     * @brief cameraReleativePositionChanged This signal emot when releative position of camera cahged.
     */
    void cameraReleativePositionChanged();

    /**
     * @brief sigLoadProgressChanged This signal emit when progress of the loading lvl changed.
     * @brief progress - This is integer value of the loading progress. (availabel ranges: 0% - 100%)
     */
    void sigLoadProgressChanged(int progress);

    /**
     * @brief worldStatusChanged This signal emited when world status has been changed
     */
    void worldStatusChanged();

    /**
     * @brief cameraRatationChanged This method emited when ratation of the camera cahnged
     */
    void cameraRatationChanged();

    /**
     * @brief playerChanged This signal eited when player are changed.
     */
    void playerChanged();

    /**
     * @brief hdrChanged This signal emited when the hdr map are changed.
     */
    void hdrChanged();

protected:

    /**
     * @brief setPlayer This method sets new player object
     * @param newPlayer This is new player object.
     * @note This method remove old player object if it exists
     */
    void setPlayer(QObject *newPlayer);

    /**
     * @brief generate This method shold be generate object from the  @a objectType.
     *  Override this method for add support yourown objects.
     *  @note If your objects not requre custom setting then use the default implementation of the generate method.
     * @param objectType This is string type name of the object,
     * @return pointer to the object.
     *
     * **Example**
     * ```cpp
     * IWorldItem* generate(const QString& objectType)) const {
     *     auto registeredObject = IWorld::generate(objectType);
     *     if (registeredObject) {
     *     // process creating of object.
     *     }
     *     return registeredObject;
     * }
     * ```
     */
    virtual IWorldItem* generate(const QString& objectType) const;

    /**
     * @brief setCameraReleativePosition This method update camera position
     * @param newCameraReleativePosition This is new camera position releative of player.
     */
    void setCameraReleativePosition(const QVector3D &newCameraReleativePosition);

    /**
     * @brief setCameraRatation This method sets new ratation of the camera.
     * @param newCameraRatation new ratation of the camera.
     */
    void setCameraRatation(const QQuaternion &newCameraRatation);

    /**
     * @brief targetFps This method return current targetFps;
     * @return current target FPS.
     */
    int targetFps() const;

    /**
     * @brief setTargetFps This method sets new targetFps.
     * @param newTargetFps This is new value of target Fps;
     */
    void setTargetFps(int newTargetFps);

    /**
     * @brief setHdr This method sets new path to hdr map of this lvl.
     * @param hdr path to hdr map.
     */
    void setHdr(const QString& hdr);

    template<class Type>

    /**
     * @brief registerObject This method will register object type for generation on the world.
     *
     * Example of use:
     *
     * ```cpp
     * ...
     * QString className = registerObject<MyType>();
     * ...
     * ```
     *
     * @return name of registered class.
     */
    QString registerObject() {

        static_assert(std::is_base_of_v<IWorldItem, Type>,
                "You try register no IWorldItem class. Please inherit of IWorldItem class and try again");

        QString type = Type().className();

        if (!_registeredTypes.contains(type)) {

            auto wraper = []() {
                return new Type();
            };

            _registeredTypes.insert(type, wraper);
        }

        return type;
    }

private slots:

    /**
     * @brief handleStop This slot invoked when user click return main menu button.
     */
    void handleStop();

private:
    /**
     * @brief prepare This method initialize world object.
     * @note If object alredy initalize then this method do nothing.
     * @return true if world initialized successful
     */
    bool prepare();
    void reset();


    /**
     * @brief running This varibale check in render function if the running is true then render loop are working correctly
     * @return
     */
    bool running() const;

    /**
     * @brief setRunning
     * @param newRunning
     */
    void setRunning(bool newRunning);

    /**
     * @brief worldChanged This method generate diff for the qml
     * @param objects This is list of object on lvl
     * @note This method addd player object to this list.
     */
    void worldChanged(WorldObjects objects);

    void clearItems();

    /**
     * @brief addItem This method remove object from the scane. If object are calster then this method remove all child objects.
     * @param obj pointer to any engine object.
     * @param addedObjectsList This is list of added items into world.
     */
    void addItem(IWorldItem *obj,
                 QList<int>* addedObjectsList = nullptr);

    /**
     * @brief removeItem This method remove item from the world. If the @a id are id of the claster object then its child object will be removed too.
     * @param id This is id of removed object.
     * @param removedObjectsList This is list of removed objects. Leave this argument nullptr for ignore this argument.
     * @note this is wrapper of the removeItem(IWorldItem*, QList<int>*);
     */
    void removeItem(int id,
                    QList<int>* removedObjectsList = nullptr);

    /**
     * @brief removeItem This method remove item from the world. If the @a id are id of the claster object then its child object will be removed too.
     * @param item This is object than will be removed.
     * @param removedObjectsList This is list of removed objects. Leave this argument nullptr for ignore this argument.
     */
    void removeItem(IWorldItem* item,
                    QList<int>* removedObjectsList = nullptr);

    /**
     * @brief addAtomicItem This method execure atomic operation of add new item. This method support only atomic objects. (not clasters)
     * @param obj This is pointer to the atomic object. If the object are claster then it will be added without childs objects.
     */
    void addAtomicItem(IWorldItem *obj);

    /**
     * @brief removeAtomicItem This method remove object with @a id. This method work with atomic objects only. If you rty remove claster objects then it will be ramoved witohout child objects.
     * @param id This is id of removed objects.
     * @return return true if object remove successul
     */
    bool removeAtomicItem(int id);

    /**
     * @brief removeAtomicItem This method remove object @a obj. This method work with atomic objects only. If you rty remove claster objects then it will be ramoved witohout child objects.
     * @param obj This is id of removed objects.
     * @return return true if object remove successul
     */
    bool removeAtomicItem(IWorldItem *obj);

    /**
     * @brief removeAnyItemFromGroup This method remove any object from group and return id of removed object. If The objec are claster then this method remove all child objects.
     * @param group This is name of the objects group
     * @param removedObjectsList This is list of removed objcts.
     * @return id of removed object.
     */
    void removeAnyItemFromGroup(const QString &group,
                                QList<int>* removedObjectsList = nullptr);

    QHash<int, IWorldItem*> _items;
    QMultiHash<QString, int> _itemsGroup;
    QMultiHash<QString, int> _lastItemsGroup;

    mutable QMutex _ItemsMutex;

    QVector3D _cameraReleativePosition;
    QQuaternion _cameraRatation;

    QString _hdrMap;
    WorldRule *_worldRules = nullptr;
    IPlayer *_player = nullptr;
    IControl *_userInterface = nullptr;
    IAI *_backgroundAI = nullptr;
    int _worldStatus = 0;
    QHash<QString, std::function<IWorldItem*()>> _registeredTypes;

    int _targetFps = 60;
    bool _running = false;

    // engine
    friend class Engine;

    // testing
    friend ClastersTest;
};

}
#endif // CRAWL_IWORLD_H
