#ifndef SNAKEPROJECT_GLOBAL_H
#define SNAKEPROJECT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SnakeProject_LIBRARY)
#  define SNAKEPROJECT_EXPORT Q_DECL_EXPORT
#else
#  define SNAKEPROJECT_EXPORT Q_DECL_IMPORT
#endif

#endif // QTSECRET_GLOBAL_H
