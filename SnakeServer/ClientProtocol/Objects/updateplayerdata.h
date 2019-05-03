#ifndef UPDATEPLAYERDATA_H
#define UPDATEPLAYERDATA_H

#include "basenetworkobject.h"
namespace ClientProtocol {


class UpdatePlayerData : public BaseNetworkObject
{
private:
    SHA256 token;

public:
    UpdatePlayerData();
    SHA256 getToken() const;
    void setToken(const SHA256 &value);

    BaseNetworkObject *create() const override;
    NetworkClassSize classSize() const override;
    QDataStream &writeToStream(QDataStream &stream) const override;
    QDataStream &readFromStream(QDataStream &stream) override;
    bool isValid() const override;
};

}
#endif // UPDATEPLAYERDATA_H
