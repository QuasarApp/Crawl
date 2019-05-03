#ifndef LOGIN_H
#define LOGIN_H

#include "basenetworkobject.h"
namespace ClientProtocol {

class Login : public BaseNetworkObject
{

private:
    SHA256 hashPass;
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
    SHA256 getHashPass() const;
    void setHashPass(const SHA256 &value);
};
}
#endif // LOGIN_H
