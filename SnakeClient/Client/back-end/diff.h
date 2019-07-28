#ifndef DIFF_H
#define DIFF_H

#include <QObject>
#include "client_global.h"

class CLIENTSHARED_EXPORT Diff
{
    Q_GADGET
private:
    QList<int> removeIds;
    QList<int> addedIds;
public:
    explicit Diff();

    Q_INVOKABLE QList<int> getRemoveIds() const;
    void setRemoveIds(const QList<int> &value);
    Q_INVOKABLE QList<int> getAddedIds() const;
    void setAddedIds(const QList<int> &value);
};

Q_DECLARE_METATYPE(Diff)

#endif // DIFF_H
