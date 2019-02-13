#ifndef BASEITEM_H
#define BASEITEM_H
#include "clientprotocol_global.h"
#include <QDataStream>


class ServerFactory;

namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT BaseItem {
private:
    unsigned int _id = 0;
public:
    explicit BaseItem(unsigned int _id);

    virtual ~BaseItem();

    virtual QDataStream &operator >>(QDataStream& stream) const;
    virtual QDataStream &operator <<(QDataStream& stream);
    bool operator ==(const BaseItem&);

    virtual bool isValid();

    friend ServerFactory;
    unsigned int id() const;
};

}


#endif // BASEITEM_H
