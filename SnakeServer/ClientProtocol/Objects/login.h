#ifndef LOGIN_H
#define LOGIN_H

#include "basenetworkobject.h"
namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT Login : public BaseNetworkObject
{

private:
    QByteArray hashRsaPass;
    QString gmail;

public:
    Login();

    BaseNetworkObject *create() const override;
    NetworkClassSize classSize() const override;
    QDataStream &writeToStream(QDataStream &stream) const override;
    QDataStream &readFromStream(QDataStream &stream) override;
    bool isValid() const override;
    QString getGmail() const;
    void setGmail(const QString &value);
    QByteArray getHashPass() const;
    void setHashPass(const QByteArray &value);
};
}
#endif // LOGIN_H
