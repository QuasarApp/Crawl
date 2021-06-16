#ifndef DIFF_H
#define DIFF_H

#include <QObject>

class GuiObject;

/**
 * @brief The Diff class contains list of the last changes on a game world.
 */
struct Diff {
    QList<int> removeIds;
    QList<GuiObject*> addedIds;
};

Q_DECLARE_METATYPE(Diff)

#endif // DIFF_H
