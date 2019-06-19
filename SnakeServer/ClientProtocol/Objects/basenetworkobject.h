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

enum cryptoAlghoritms: int {
    RSA64 = 0x0,
    RSA128 = 0x1,
    SHA256 = 0x2,

    Key = 0x100
};

template <typename T>
NetworkClassSize getTypeSize(const T& type = {}, int alg = SHA256) {
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

        bool isKey = alg & Key;

        switch (alg & ~Key) {
        case RSA64: {

            if (isKey) {
                return {
                    static_cast<unsigned int>(sizeof (int) +
                            QRSAEncryption::getKeyBytesSize(QRSAEncryption::RSA_64))
                };
            }

            return {
                static_cast<unsigned int>(sizeof (int) +
                        QRSAEncryption::getKeyBytesSize(QRSAEncryption::RSA_64)),

                static_cast<unsigned int>(sizeof (int) +
                        QRSAEncryption::getKeyBytesSize(QRSAEncryption::RSA_64) * 2)

            };
        }
        case RSA128: {
            if (isKey) {
                return {
                    static_cast<unsigned int>(sizeof (int) +
                            QRSAEncryption::getKeyBytesSize(QRSAEncryption::RSA_128))
                };
            }

            return {
                static_cast<unsigned int>(sizeof (int) +
                        QRSAEncryption::getKeyBytesSize(QRSAEncryption::RSA_128)),

                static_cast<unsigned int>(sizeof (int) +
                        QRSAEncryption::getKeyBytesSize(QRSAEncryption::RSA_128) * 2)

            };

        }

        case SHA256: {
            return {sizeof (int) + 32};
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
