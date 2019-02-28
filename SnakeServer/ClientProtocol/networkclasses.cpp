#include "networkclasses.h"
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

bool NetworkClasses::isInteger(NetworkClasses::Type type) {
    return type == Int || type == UInt || type == Char ||
            type == UChar || type == Short ||
            type == UShort || type == SHA256;
}

bool NetworkClasses::isReal(NetworkClasses::Type type) {
    return type == Float || type == UFloat || type == Double ||
            type == UDouble;
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

int NetworkClasses::getSizeType(NetworkClasses::Type type) {
    switch (type) {
    case Char:
    case UChar: return sizeof (char);
    case Short:
    case UShort: return sizeof(short);
    case Int:
    case UInt: return sizeof(int);
    case Float:
    case UFloat: return sizeof (float);
    case Double:
    case UDouble: return sizeof (double);
    case SHA256: return 32;
    default: return 0;
    }
}

}
