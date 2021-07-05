//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef DIFF_H
#define DIFF_H

#include <QList>
#include <QObject>

namespace CRAWL {

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

}
Q_DECLARE_METATYPE(CRAWL::Diff)

#endif // DIFF_H
