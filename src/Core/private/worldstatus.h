//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef WORLDSTATUS_H
#define WORLDSTATUS_H

#include <QObject>

/**
 * @brief The WorldStatus enum This enum contains statuses of the world.
 * @note This statuses available only internal in main engine library.
 */
namespace WorldStatus
{
    Q_NAMESPACE         // required for meta object creation
    /**
     * @brief The WorldStatus enum This enum contains statuses of the world.
     * @note This statuses available only internal in main engine library.
     */
    enum Status {
        /// Undefined status. Using by default
        Undefined = 0,
        /// World with this status emit random control signals for the player object fir emulate game session of the AI.
        Background,
        /// World with this status show hame control menu and listem player signals.
        Game
    };
    Q_ENUM_NS(Status)  // register the enum in meta object data
}

#endif // WORLDSTATUS_H
