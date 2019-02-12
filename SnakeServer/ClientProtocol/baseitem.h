#ifndef BASEITEM_H
#define BASEITEM_H
#include "clientprotocol_global.h"
#include <QDataStream>


class ServerFactory;

namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT BaseItem {
private:
    unsigned int _id = 0;
protected:
    BaseItem();

public:
    virtual ~BaseItem();

    virtual QDataStream &operator >>(QDataStream& stream) const;
    virtual QDataStream &operator <<(QDataStream& stream);

    virtual bool isValid();

    friend ServerFactory;
};

}


#endif // BASEITEM_H
