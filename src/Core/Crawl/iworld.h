//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IWORLD_H
#define IWORLD_H

#include "iplayer.h"

#include <QHash>
#include <QMap>
#include <QMultiHash>
#include <QObject>
#include <QQuaternion>
#include <QString>
#include "irender.h"
#include "diff.h"
#include "global.h"

class IWorldItem;
class IPlayer;
class IGround;
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
 * @brief The WorldObjectWraper struct This is simple wraper structure for the internal functionality of the IWorld objects.
 */
struct WorldObjectWraper {
    IWorldItem* objectPtr = nullptr;
    QString groupName = "";
};

/**
 * @brief The IWorld class use this interface for implementation your own game levels
 */
class CRAWL_EXPORT IWorld : public QObject, public IRender
{
    Q_OBJECT
    Q_PROPERTY(QVector3D cameraReleativePosition READ cameraReleativePosition NOTIFY cameraReleativePositionChanged)
    Q_PROPERTY(QQuaternion cameraRatation READ cameraRatation NOTIFY cameraRatationChanged)

    Q_PROPERTY(int worldStatus READ wordlStatus WRITE setWorldStatus NOTIFY worldStatusChanged)

public:
    IWorld();
    virtual ~IWorld();

    /**
     * @brief generateGroundTile This method should be generate a new tile of the world.
     * @return raw pointer to tile of the world ground.
     * @note The tile count sets automaticly.
     * @note All generated objects will be distroed automaticaly.
     */
    virtual IGround* generateGroundTile() = 0;

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
     * @brief hdrMap This method return path to hdr map of world.
     * @return
     */
    const QString &hdrMap() const;

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
    void sigOBjctsListChanged(Diff diff);

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

protected:

    /**
     * @brief generate This method shold be generate object from the  @a objectType.
     *  Override this method for add support yourown objects.
     * @param objectType This is string type name of the object,
     * @return pointer to the object.
     */
    virtual IWorldItem* generate(const QString& objectType) const = 0;

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

private slots:
    void handleStop();

private:
    /**
     * @brief init This method initialize world object.
     * @note If object alredy initalize then this method do nothing.
     * @return
     */
    bool init();
    void deinit();

    void generateGround();
    void worldChanged(const WorldObjects& objects);
    void clearItems();
    void addItem(const QString &group, IWorldItem *obj);

    /**
     * @brief removeItem This method remove object with @a id.
     * @param id This is id of removed objects.
     * @return return true if object remove successul
     */
    bool removeItem(int id);

    /**
     * @brief removeAnyItemFromGroup This method remove any object from group and return id of removed object.
     * @param group This is name of the objects group
     * @return id of removed object.
     * @note if object not removed return 0
     */
    int removeAnyItemFromGroup(const QString &group);

    QHash<int, WorldObjectWraper> _items;
    QMultiHash<QString, int> _itemsGroup;
    QVector3D _cameraReleativePosition;
    QQuaternion _cameraRatation;

    QString _hdrMap;
    WorldRule *_worldRules = nullptr;
    IPlayer *_player = nullptr;
    IControl *_userInterface = nullptr;
    IAI *_backgroundAI = nullptr;

    friend class Engine;
    int _worldStatus = 0;
};

#endif // IWORLD_H
