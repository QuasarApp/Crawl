#ifndef BASENETWORKOBJECT_H
#define BASENETWORKOBJECT_H

#include "networkclasssize.h"

#include <cstdlib>
#include <QDataStream>
#include <QVector>
#include <typeinfo>
#include "config.h"
#include <type_traits>
#include "clientprotocol_global.h"
#include <qrsaencryption.h>

namespace ClientProtocol {

enum cryptoAlghoritms: unsigned int {
    RSA = 0x0,
    SHA = 0x2,

    Key = 0x100
};

struct EncryptionParams {
    unsigned int alg = SHA;
    unsigned int baseBits = QRSAEncryption::RSA_256;
    unsigned int encryptBits = QRSAEncryption::RSA_256;
};

template <typename T>
NetworkClassSize getTypeSize(const T& type = {}, EncryptionParams params = {}) {

    auto hash = typeid(type).hash_code();

    if (hash == typeid(QString).hash_code()) {

        return { sizeof (int), sizeof (QChar) * MAX_SIZE};

    } else if (hash == typeid(QList<int>).hash_code()) {

        return { sizeof (int), sizeof (int) * MAX_SIZE};

    } else if (hash == typeid(QList<float>).hash_code()) {

        return { sizeof (float), sizeof (float) * MAX_SIZE};

    } else if (hash == typeid(QStringList).hash_code()) {

        auto size = getTypeSize<QString>();
        return {sizeof (int) , size.max + static_cast<int>(sizeof (int) * MAX_SIZE)};

    } else if (hash == typeid(QByteArray).hash_code()) {

        bool isKey = params.alg & Key;

        switch (params.alg & ~Key) {
        case RSA: {

            if (isKey) {

                return {
                    static_cast<unsigned int>(sizeof (int) +
                            QRSAEncryption::getKeyBytesSize(static_cast<QRSAEncryption::Rsa>(params.baseBits)))
                };
            }

            auto baseSize =
                    static_cast<unsigned int>(sizeof (int) +
                    QRSAEncryption::getKeyBytesSize(static_cast<QRSAEncryption::Rsa>(params.encryptBits))) / 2;

            return {baseSize, baseSize * params.baseBits};
        }

        case SHA: {
            return {static_cast<unsigned int>(sizeof (int) + params.baseBits)};
        }
        default:
            return sizeof (int) + 10;
        }

    }
    return sizeof (type);
}

class CLIENTPROTOCOLSHARED_EXPORT BaseNetworkObject
{
private:
    int _id = -1;
protected:
    quint8 _class = 0;

public:
    BaseNetworkObject();
    virtual BaseNetworkObject* create() const;
    virtual ~BaseNetworkObject();

    virtual NetworkClassSize classSize() const;
    virtual QDataStream& writeToStream(QDataStream& stream) const;
    virtual QDataStream& readFromStream(QDataStream& stream);
    virtual bool isValid() const;
    void toBytes(QByteArray& array) const;
    void fromBytes(const QByteArray& array);
    int id() const;
    void setId(int id);
    quint8 getClass() const;
};

template<class T>
auto cast(const BaseNetworkObject* obj) {
    static_assert (!std::is_pointer<T>(), "Cast working only with pointers!");
    return static_cast<T>(obj);
}

}
#endif // BASENETWORKOBJECT_H
