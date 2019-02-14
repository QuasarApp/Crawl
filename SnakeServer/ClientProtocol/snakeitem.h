#ifndef SNAKEITEM_H
#define SNAKEITEM_H
#include "baseitem.h"

#include <QVector>
#define SNAKE_MAX_SIZE 15


namespace ClientProtocol {

constexpr int snakeSize = SNAKE_MAX_SIZE * sizeof (float) + 2;

class CLIENTPROTOCOLSHARED_EXPORT SnakeItem: public BaseItem
{

public:
    SnakeItem() = delete;

    static bool read(QDataStream &stream, QVariantMap &map);
    static bool write(QDataStream &stream, const QVariantMap &map);
};
}



#endif // SNAKEITEM_H
