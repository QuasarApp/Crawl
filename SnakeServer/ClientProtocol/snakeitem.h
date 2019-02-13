#ifndef SNAKEITEM_H
#define SNAKEITEM_H
#include "baseitem.h"

#include <QVector>
#define SNAKE_MAX_SIZE 15


namespace ClientProtocol {

constexpr int snakeSize = SNAKE_MAX_SIZE * 4 + 1;

class CLIENTPROTOCOLSHARED_EXPORT SnakeItem: public BaseItem
{
private:
    unsigned char _spead = 0;
    QVector<float> _skillet;

public:
    explicit SnakeItem(unsigned int id);
    ~SnakeItem() override;

    bool isValid() override;

    QDataStream &operator <<(QDataStream &stream) override;
    QDataStream &operator >>(QDataStream &stream) const override;
};
}



#endif // SNAKEITEM_H
