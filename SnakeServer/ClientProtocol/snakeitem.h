#ifndef SNAKEITEM_H
#define SNAKEITEM_H
#include "baseitem.h"

#include <QVector>

namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT SnakeItem: public BaseItem
{
private:
    unsigned int _spead = 0;
    QVector<double> _skillet;

public:
    explicit SnakeItem(unsigned int id);
    ~SnakeItem() override;

    bool isValid() override;

    QDataStream &operator <<(QDataStream &stream) override;
    QDataStream &operator >>(QDataStream &stream) const override;
};
}



#endif // SNAKEITEM_H
