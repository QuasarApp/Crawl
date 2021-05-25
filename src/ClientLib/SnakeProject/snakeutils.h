#ifndef SNAKEUTILS_H
#define SNAKEUTILS_H


#include <QMap>
#include <QPoint>
#include <QVariant>

/**
 * @brief WorldRules
 * this map conteins:
 * 1. list of generated objects and they count.
 * 2. long of world (Long),
 * 3. spead of world (Spead),
 * !!!Note: all object show on map alltime.
 */
typedef QMap<QString, int> WorldRules;


#endif // SNAKEUTILS_H
