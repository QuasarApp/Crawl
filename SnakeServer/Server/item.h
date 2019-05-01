#ifndef ITEM_H
#define ITEM_H
#include <clientprotocol.h>
#include <clientprotocol_global.h>

class Item : protected ClientProtocol::Package
{
private:

    int id = -1;

public:
    Item(const ClientProtocol::Package& other);
    Item(const ClientProtocol::BaseNetworkObject* obj);
    ~Item() override;
    ClientProtocol::Command cmd() const;
    const QByteArray& dataArray() const;
    bool isValid() const override;
    int getId() const;
    void setId(int value);
};

#endif // ITEM_H
