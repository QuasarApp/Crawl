#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QQmlEngine>
#include <SnakeProject/diff.h>

class IWorld;

/**
 * @brief The Engine class
 */
class Engine : public QObject {

    Q_OBJECT
    Q_PROPERTY(QString hdr READ hdr NOTIFY hdrChanged)
    Q_PROPERTY(QObject* player READ player NOTIFY playerChanged)
    Q_PROPERTY(QObject* world READ world NOTIFY worldChanged)

    Q_PROPERTY(QObject* scane READ scane WRITE setScane NOTIFY scaneChanged)
    Q_PROPERTY(QObject* menu READ menu WRITE setMenu NOTIFY menuChanged)

public:
    Engine(QObject * parent = nullptr);

    /**
     * @brief scane This method return main scane of the game.
     * @return pointer to main game scane.
     */
    Q_INVOKABLE QObject* scane();

    /**
     * @brief setQmlEngine This method sets qml engine
     * @param newEngine This is pointer to the qml engine.
     */
    void setQmlEngine(QQmlEngine *newEngine);

    /**
     * @brief setWorld This method set new world for game.
     * @param world This is pointer to new world.
     */
    void setWorld(IWorld *world);

    /**
     * @brief hdr This method should return hdr map of the lvl
     * @return path to hdr map.
     */
    QString hdr() const;

    /**
     * @brief setScane This method sets new scane object. The scane object are
     * @param newScane are Qt Quick 3d node object form qml.
     */
    void setScane(QObject *newScane);

    /**
     * @brief currentWorld return pointer to current world object.
     * @return raw pointer to current world object.
     */
    IWorld *currentWorld() const;

    /**
     * @brief player return player object.
     * @return player object
     */
    QObject* player() const;

    /**
     * @brief world return player object.
     * @return world object
     */
    QObject* world() const;

    QObject *menu() const;
    void setMenu(QObject *newMenu);

private slots:

    /**
     * @brief handleGameObjectsChanged This slot invoked when games objects changed.
     * @brief diff this is changes of the lvl.
     */
    void handleGameObjectsChanged(Diff diff);

signals:
    void hdrChanged();
    void scaneChanged();
    void playerChanged();
    void worldChanged();

    void menuChanged();

private:
    bool add(GuiObject* obj);
    bool remove(int id);

    QObject *_scane = nullptr;
    QQmlEngine *_engine = nullptr;
    QHash<int, QObject*> _qmlObjects;
    IWorld* _currentWorld = nullptr;
    QObject *_menu = nullptr;
};

#endif // ENGINE_H
