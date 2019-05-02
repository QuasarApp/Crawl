#ifndef ITEM_H
#define ITEM_H
#include <clientprotocol.h>
#include <clientprotocol_global.h>

class Item : protected ClientProtocol::Package
{
private:

    int id = -1;

public:
    Item();
    Item(const ClientProtocol::Package& other);
    Item(const ClientProtocol::BaseNetworkObject* obj);
    Item(ClientProtocol::Command cmd, const QByteArray& data);

    ~Item() override;
    ClientProtocol::Command cmd() const;
    const QByteArray& dataArray() const;
    bool isValid() const override;
    int getId() const;
    void setId(int value);
    template<class T>
    bool parse(T& res) {
        return ClientProtocol::Package::parse(res);
    }
};

#endif // ITEM_H
