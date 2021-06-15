//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

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
