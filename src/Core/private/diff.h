#ifndef DIFF_H
#define DIFF_H

#include <QObject>

class GuiObject;

/**
 * @brief The Diff class contains list of the last changes on a game world.
 */
class Diff {
private:
    QList<int> removeIds;
    QList<GuiObject*> addedIds;
public:
    explicit Diff();

    Q_INVOKABLE const QList<int> &getRemoveIds() const;
    void setRemoveIds(const QList<int> &value);
    Q_INVOKABLE const QList<GuiObject *> &getAddedIds() const;
    void setAddedIds(const QList<GuiObject*> &value);
};

Q_DECLARE_METATYPE(Diff)

#endif // DIFF_H
