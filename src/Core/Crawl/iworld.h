//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef CRAWL_IWORLD_H
#define CRAWL_IWORLD_H

#include "gameresult.h"
#include "iitem.h"
#include "playableobject.h"
#include "startdata.h"

#include <QFuture>
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

/**
 * @brief The Events enum contains availabele events of the World.
 */
enum Events {
    /// If object support this event then for them will be check intersection with all not decorative objects.
    Intersects = 0x01,
};

class IWorldItem;
class PlayableObject;
class GroundClaster;
class IControl;
class IAI;
class IWorldLight;
class EventServer;
class Player;

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
class CRAWL_EXPORT IWorld : public QObject, public IRender, public IItem
{
    Q_OBJECT
    Q_PROPERTY(QVector3D cameraReleativePosition READ cameraReleativePosition NOTIFY cameraReleativePositionChanged)
    Q_PROPERTY(QQuaternion cameraRotation READ cameraRotation NOTIFY cameraRotationChanged)
    Q_PROPERTY(QObject * player READ player WRITE setPlayer NOTIFY playerChanged)

    /**
     * @brief menu This propertye contains user interface model that initialised on the IWorld::userInterface method. For get more information see the IContol class.
     * @see IWorld::getMenu
     * @see IWorld::userInterface
    */
    Q_PROPERTY(QObject * menu READ getMenu NOTIFY menuChanged)
    Q_PROPERTY(QString hdr READ hdr NOTIFY hdrChanged)
    Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)

    Q_PROPERTY(int worldStatus READ wordlStatus WRITE setWorldStatus NOTIFY worldStatusChanged)

public:
    /**
     * @brief IWorld This main constructor of the world object. You need to initialize all chold items of the world using the IItem::AddChildItem method.
     */
    IWorld();
    ~IWorld() override;

    /**
     * @brief initPlayer The implementation of This interface must be return playerObject by type. This method should be generate new object of the player by type.
     * @param objectType This is type of requried snake object. See the IItem::itemId method.
     * @return raw pointer to the player object.
     * @note The Palyer object will be deleted when wold distroed.
     *  So do not delete your created player pbject yuorself.
     */
    virtual PlayableObject* initPlayer(int objectType) const = 0;

    QString itemTextType() const override;

    /**
     * @brief type This method return const string value of the all world types.
     * @return const string value of the all world types.
     * @see IItem::itemTextType
     * @see IItem::type
     */
    static QString typeText();

    /**
     * @brief type This is wrapper of the IWorld::typeText method that invoke the qHash function for results string.
     * @return integer type object id.
     */
    static unsigned int type();

    void init() override;

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
    virtual IControl *initUserInterface() const;

    /**
     * @brief initHdrBackGround The implementation of this method must be return valid path to the hdr image map.
     * The hdr image map it is background jpeg image.
     * @return path to hfr map.
     */
    virtual QString initHdrBackGround() const = 0;

    /**
     * @brief render this method recursive invoke all render functions of the all world items.
     *  The render function is main function of the SnakeEngine This method recal all propertys of all objects.
     */
    virtual void render(unsigned int tbfMsec) override;

    /**
     * @brief initControl This method should be configure all connections of @a control object.
     * @param control This is control object
     * @note override this method if you have own IControl object.
     */
    virtual void initControl(IControl* control);

    /**
     * @brief start This method will be invoked when user click start button.
     * @param config This is initialize level arguments.
     * @note The Default implementation reset all positions for all objects.
     * @return true if game started successful.
     */
    virtual bool start(const StartData &config);

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
    Q_INVOKABLE IWorldItem *getItem(int id) const;

    /**
     * @brief cameraReleativePosition return  a releative of player camera position.
     * @return
     */
    const QVector3D &cameraReleativePosition() const;

    /**
     * @brief userInterface This method return pointer to userinterface.
     * @return pointer to user interface
     */
    IControl *userInterface();

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
    IAI *backgroundAI();

    /**
     * @brief cameraRotation This method return curent camera rotation.
     * @return Quaternion of camera rotation
     */
    const QQuaternion &cameraRotation() const;

    /**
     * @brief player This method return player object
     * @return player object
     */
    QObject *player() const;

    /**
     * @brief hdr This method return path to hdr map of the lvl.
     * @return path to hdr map of this lvl.
     */
    const QString &hdr();

    /**
     * @brief runAsBackGround This method run this world as a backgroud.
     * The player start new game and sets new control from the backgroundAI method.
     */
    void runAsBackGround();

    /**
     * @brief menu This method return current pointer to the user interface of this world.
     * @return pointer of the user Interface of this world.
     * @see IWorld::menu
     * @see IWorld::userInterface
     */
    QObject *getMenu();

    /**
     * @brief reset This method reset all world objects.
     */
    void reset();

    /**
     * @brief visible This metohd retunr current value of the visible object.
     * @return true if view is visible else false.
     */
    bool visible() const;

signals:
    /**
     * @brief sigGameFinished This signal emit when game are finished
     */
    void sigGameFinished() const;

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
     * @brief cameraRotationChanged This method emited when rotation of the camera cahnged
     */
    void cameraRotationChanged();

    /**
     * @brief playerChanged This signal eited when player are changed.
     */
    void playerChanged();

    /**
     * @brief hdrChanged This signal emited when the hdr map are changed.
     */
    void hdrChanged();

    /**
     * @brief sigWorldChanged emit this signal if you want to change level of the world.
     * @note this signal needed for the move WorldChange method into main thread.
     * @param objects this is iterator of the world rule object.
     */
    void sigWorldChanged(WorldRule::const_iterator objects);

    /**
     * @brief menuChanged This signal emited when user interface is changed.
     */
    void menuChanged();

    /**
     * @brief visibleChanged This signal emited when visible of the view changed.
     */
    void visibleChanged();

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
     * @brief setCameraRotation This method sets new rotation of the camera.
     * @param newCameraRotation new rotation of the camera.
     */
    void setCameraRotation(const QQuaternion &newCameraRotation);

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

    /**
     * @brief updateWorld This method check current distance and load neede level and level objects.
     */
    void updateWorld();

    /**
     * @brief worldRules This method return world cure map.
     * @return world rule map.
     */
    const WorldRule *worldRules();

    /**
     * @brief setVisible This method sets visible propertye for the qml view.
     * @param visible This is new value of a property
     */
    void setVisible(bool visible);

    /**
     * @brief playerIsDead This method will be invoked when player object get signal dead.
     */
    virtual void playerIsDead(PlayableObject*);

    /**
     * @brief isRendering This method erturn true if the render loop is working else false.
     * @return true if the render loop is working else false.
     * @see IWorld::stopRenderLoop
     * @see IWorld::startRenderLoop
     */
    bool isRendering() const;

    /**
     * @brief stopRenderLoop This method stop render loop in engine.
     * @see IWorld::isRendering
     * @see IWorld::startRenderLoop
     */
    void stopRenderLoop();

    /**
     * @brief startRenderLoop This method start render loop in engine.
     * @see IWorld::stopRenderLoop
     * @see IWorld::isRendering
     */
    void startRenderLoop();

    /**
     * @brief stopRenderLoopWithClearItems This method stoped render loop and clear all created items.
     * @see IWorld::stopRenderLoop
     */
    void stopRenderLoopWithClearItems();

protected slots:
    virtual void onIntersects(const IWorldItem * trigger, QList<const IWorldItem *> list);

    /**
     * @brief worldChanged This method generate diff for the qml
     * @param objects This is iterator of the world rules object that contains list of object on lvl
     * @note This method addd player object to this list.
     */
    void worldChanged(WorldRule::const_iterator objects);

private slots:

    /**
     * @brief handleStop This slot invoked when user click return main menu button.
     */
    void handleStop();

private:
    /**
     * @brief clearItems This method remove all created items from world.
     */
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

    void renderLoop();
    QFuture<void> _renderLoopFuture;

    EventServer * _eventServer = nullptr;

    QHash<int, IWorldItem*> _items;
    QMultiHash<QString, int> _itemsGroup;
    QMultiHash<QString, int> _lastItemsGroup;

    mutable QMutex _ItemsMutex;

    QVector3D _cameraReleativePosition;
    QQuaternion _cameraRotation;

    QString _hdrMap;
    WorldRule *_worldRules = nullptr;
    WorldRule::const_iterator _currendWorldLevel;

    PlayableObject *_player = nullptr;
    IAI *_backgroundAI = nullptr;
    IControl *_userInterface = nullptr;

    int _worldStatus = 0;
    QHash<QString, std::function<IWorldItem*()>> _registeredTypes;

    int _targetFps = 60;
    quint64 _oldTimeRender = 0;

    bool _visible = true;
    bool _renderLoop = false;

    // testing
    friend ClastersTest;

};

}
#endif // CRAWL_IWORLD_H
