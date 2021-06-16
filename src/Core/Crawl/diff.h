#ifndef DIFF_H
#define DIFF_H

#include <QList>
#include <QObject>

class GuiObject;

/**
 * @brief The Diff class contains list of the last changes on a game world.
 */
class Diff {
    Q_GADGET

public:
    Q_INVOKABLE QList<int> getRemoveIds() const;
    Q_INVOKABLE QList<int> getAddedIds() const;

    QList<int> removeIds;
    QList<int> addedIds;
};

Q_DECLARE_METATYPE(Diff)

#endif // DIFF_H
