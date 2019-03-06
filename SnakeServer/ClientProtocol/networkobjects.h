#ifndef NETWORKOBJECTS_H
#define NETWORKOBJECTS_H
#include <QHash>
#include "snakeutils.h"
#include "networkclasses.h"

namespace ClientProtocol {

extern const QHash<NetworkClasses::Type, QMap<QString, NetworkClasses::Type>> networkObjects;
}
#endif // NETWORKOBJECTS_H
