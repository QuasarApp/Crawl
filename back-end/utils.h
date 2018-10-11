#ifndef UTILS_H
#define UTILS_H

#include <QMap>
#include <QPoint>

/**
 * @brief WorldRules
 * this map conteins:
 * 1. list of generated objects and they count.
 * 2. long of world (Long),
 * 3. spead of woeld (Spead),
 * !!!Note: all object show on map alltime.
 */
typedef QMap<QString, int> WorldRules;

namespace Global {
    extern QPoint deviceSize;
};

#endif // UTILS_H
