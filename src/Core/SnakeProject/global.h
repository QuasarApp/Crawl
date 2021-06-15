//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef SNAKEPROJECT_GLOBAL_H
#define SNAKEPROJECT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SnakeProject_LIBRARY)
#  define SNAKEPROJECT_EXPORT Q_DECL_EXPORT
#else
#  define SNAKEPROJECT_EXPORT Q_DECL_IMPORT
#endif

#endif // QTSECRET_GLOBAL_H
