#ifndef SNAKEITEM_H
#define SNAKEITEM_H
#include "baseitem.h"

namespace ClientProtocol {

class SnakeItem: public BaseItem
{
private:
    unsigned int _spead = 0;
public:
    SnakeItem();
    ~SnakeItem() override;

    bool isValid() override;

    QDataStream &operator <<(QDataStream &stream) override;
    QDataStream &operator >>(QDataStream &stream) const override;
};
}



#endif // SNAKEITEM_H
