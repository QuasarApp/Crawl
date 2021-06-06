#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QQmlEngine>
#include <diff.h>

/**
 * @brief The Engine class
 */
class Engine : public QObject {

    Q_OBJECT

public:
    Engine();

    /**
     * @brief scane This method return main scane of the game.
     * @return pointer to main game scane.
     */
    Q_INVOKABLE QObject* scane();
    void setEngine(QQmlEngine *newEngine);

public slots:

    /**
     * @brief handleGameObjectsChanged This slot invoked when games objects changed.
     * @brief diff this is changes of the lvl.
     */
    void handleGameObjectsChanged(Diff diff);

private:
    bool add(GuiObject* obj);
    bool remove(int id);

    QObject *_scane = nullptr;
    QQmlEngine *_engine = nullptr;

    QHash<int, QObject*> _qmlObjects;
};

#endif // ENGINE_H
