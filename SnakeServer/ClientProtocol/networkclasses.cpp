#include "networkclasses.h"

#include <QVariant>
namespace ClientProtocol {

NetworkClasses::NetworkClasses()
{

}


bool NetworkClasses::isNumber(NetworkClasses::Type type) {
    return isInteger(type) || isReal(type);
}

bool NetworkClasses::isStream(NetworkClasses::Type type) {
    return isString(type) || isVariant(type);
}

bool NetworkClasses::isCustomType(NetworkClasses::Type type) {
    return (type & CustomType) && type <= LastCustomType && !(type & BaseType);
}

bool NetworkClasses::isInteger(NetworkClasses::Type type) {
    return type == Int || type == UInt || type == Char ||
            type == UChar || type == Short ||
            type == UShort || type == SHA256;
}

bool NetworkClasses::isReal(NetworkClasses::Type type) {
    return type == Float  || type == Double;
}

bool NetworkClasses::isString(NetworkClasses::Type type) {
    return type == String;
}

bool NetworkClasses::isArray(NetworkClasses::Type type) {
    return type & Array;
}

bool NetworkClasses::isVariant(NetworkClasses::Type type) {
    return type == Variant;
}

unsigned int NetworkClasses::getSizeType(NetworkClasses::Type type) {
    switch (type) {
    case Char:
    case UChar: return sizeof (char);
    case Short:
    case UShort: return sizeof(short);
    case Int:
    case UInt: return sizeof(int);
    case Float: return sizeof (float);
    case Double: return sizeof (double);
    case SHA256: return 32;
    default: return 0;
    }
}

QByteArray NetworkClasses::toByteArray(NetworkClasses::Type type, const QVariant& item) {
    switch (type) {
    case Char: {
        auto temp = static_cast<char>(item.toInt());
        return QByteArray::fromRawData(&temp, sizeof (char));
    }
    case UChar: {
        auto temp = static_cast<unsigned char>(item.toUInt());
        return QByteArray::fromRawData(reinterpret_cast<char*>(&temp), sizeof (unsigned char));
    }
    case Short: {
        auto temp = static_cast<unsigned short>(item.toInt());
        return QByteArray::fromRawData(reinterpret_cast<char*>(&temp), sizeof (unsigned short));
    }
    case UShort: {
        auto temp = static_cast<short>(item.toUInt());
        return QByteArray::fromRawData(reinterpret_cast<char*>(&temp), sizeof (short));
    }
    case Int: {
        auto temp = static_cast<int>(item.toInt());
        return QByteArray::fromRawData(reinterpret_cast<char*>(&temp), sizeof (int));
    }
    case UInt: {
        auto temp = static_cast<unsigned int>(item.toUInt());
        return QByteArray::fromRawData(reinterpret_cast<char*>(&temp), sizeof (unsigned int));
    }
    case Float: {
        auto temp = item.toFloat();
        return QByteArray::fromRawData(reinterpret_cast<char*>(&temp), sizeof (float));
    }
    case Double: {
        auto temp = item.toDouble();
        return QByteArray::fromRawData(reinterpret_cast<char*>(&temp), sizeof (double));
    }

    case SHA256: {
        return item.toByteArray();
    }
    default: return QByteArray();
    }
}

template<typename T>
QVariant rawRead(const QByteArray & arr) {
    T temp;
    memcpy(reinterpret_cast<char*>(&temp), arr.data(), sizeof (T));
    return temp;
}

QVariant NetworkClasses::fromByteArray(NetworkClasses::Type type, const QByteArray& arr) {


    switch (type) {
    case Char: {
        return rawRead<char>(arr);
    }
    case UChar: {
        return rawRead<unsigned char>(arr);
    }
    case Short: {
        return rawRead<short>(arr);
    }
    case UShort: {
        return rawRead<unsigned short>(arr);
    }
    case Int: {
        return rawRead<int>(arr);
    }
    case UInt: {
        return rawRead<unsigned int>(arr);
    }
    case Float: {
        return rawRead<float>(arr);
    }
    case Double: {
        return rawRead<double>(arr);
    }

    case SHA256: {
        return arr;
    }

    default: return QByteArray();
    }
}

}
