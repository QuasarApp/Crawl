#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include "diff.h"
#include "snake.h"
#include "world.h"

class MainMenuModel;

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int long_ READ long_ NOTIFY long_changed)
    Q_PROPERTY(int generalLong READ generalLong NOTIFY generalLongchanged)
    Q_PROPERTY(QObject* mainMenuModel READ mainMenuModel NOTIFY mainMenuModelchanged)
    Q_PROPERTY(bool showMenu READ showMenu WRITE setShowMenu NOTIFY showMenuChanged)

private:

    World world;
    QMap<int, GuiObject *> objectsContainer;
    QTimer *timer = nullptr;

    int lvl = 0;
    int m_generalLong = 0;
    bool pause = false;
    bool _showMenu = true;

    void generateDiff(const QMap<int, GuiObject *> &);

    MainMenuModel* _networkModel = nullptr;

public:
    Controller();
    ~Controller();

    void startTimer();
    void stopTimer();

    int long_() const;
    int generalLong() const;
    bool showMenu() const;

    QObject* mainMenuModel() const;

public slots:
    void buttonPress();
    void setPause(bool);
    void update();

    /**
     * @brief nextLvl - switch to next lvl from array lvels
     * @return true if all levels are passed
     */
    bool nextLvl();

    /**
     * @brief newGame - start game from first lvl
     */
    void handleNewGame();

    /**
     * @brief getGameObject
     * @param id - id of guiObject;
     * @return guiObject if (id is not valid return nullptr)
     */
    QObject* getGameObject(int id);

    void setShowMenu(bool showMenu);

signals:

    /**
     * @brief gameObjectsChanged
     * @param dif
     */
    void gameObjectsChanged(const Diff &dif);
    void long_changed(int m_long);
    void generalLongchanged(int generalLong);
    void mainMenuModelchanged(QObject* mainMenuModel);
    void showMenuChanged(bool showMenu);
};

#endif // CONTROLLER_H
