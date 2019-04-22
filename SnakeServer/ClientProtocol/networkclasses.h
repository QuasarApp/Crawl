#ifndef NETWORKCLASSES_H
#define NETWORKCLASSES_H
#include "clientprotocol_global.h"

#include <qvariant.h>

namespace ClientProtocol {

#define BEGIN_CUSTOM_TYPE
#define END_CUSTOM_TYPE LastCustomType,


class CLIENTPROTOCOLSHARED_EXPORT NetworkClasses
{

public:
    enum Type: unsigned short {
        Undefined = 0x00,

        // base types
        Char =      0x01,
        UChar =     0x02,
        Short =     0x03,
        UShort =    0x04,
        Int =       0x05,
        UInt =      0x06,
        Float =     0x07,
        Double =    0x08,
        String =    0x09,
        Variant =   0x0a,
        SHA256 =    0x0b,

        // baseArray
        Array =     0x80,

        ArrayChar =     Array | Char,
        ArrayUChar =    Array | UChar,
        ArrayShort =    Array | Short,
        ArrayUShort =   Array | UShort,
        ArrayInt =      Array | Int,
        ArrayUInt =     Array | UInt,
        ArrayFloat =    Array | Float,
        ArrayDouble =   Array | Double,
        ArrayString =   Array | String,
        ArrayVariant =  Array | Variant,

        BaseType = 0x00FF,

        BEGIN_CUSTOM_TYPE
        // custom types
        Ping =      0x0100,
        Snake =     0x0200,
        Player =    0x0300,
        Map    =    0x0400,
        Game   =    0x0500,
        Login  =    0x0600,
        UpdatePlayerData = 0x0700,
        GetItem =   0x0800,
        BadRequest = 0x0900,

        END_CUSTOM_TYPE
        // general objects
        GeneralObject = 0x8000,

        CustomType = 0xFF00,

    };

    static bool isInteger(Type);
    static bool isReal(Type);
    static bool isString(Type);
    static bool isArray(Type);
    static bool isVariant(Type);
    static bool isNumber(Type);
    static bool isStream(Type);
    static bool isCustomType(Type type);

    static unsigned int getSizeType(Type);
    static QByteArray toByteArray(NetworkClasses::Type type, const QVariant &item);
    static QVariant fromByteArray(NetworkClasses::Type type, const QByteArray &arr);

    NetworkClasses();
};
}
#endif // NETWORKCLASSES_H
