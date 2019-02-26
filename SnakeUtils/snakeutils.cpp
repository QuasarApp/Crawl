#include "snakeutils.h"


bool SnakeUtils::isNumber(SnakeUtils::Type type) {
    return isInteger(type) || isReal(type);
}

bool SnakeUtils::isStream(SnakeUtils::Type type) {
    return isString(type) || isVariant(type);
}

bool SnakeUtils::isInteger(SnakeUtils::Type type) {
    return type == SnakeUtils::Int || type == SnakeUtils::UInt || type == SnakeUtils::Char ||
            type == SnakeUtils::UChar || type == SnakeUtils::Short ||
            type == SnakeUtils::UShort || type == SnakeUtils::SHA256;
}

bool SnakeUtils::isReal(SnakeUtils::Type type) {
    return type == SnakeUtils::Float || type == SnakeUtils::UFloat || type == SnakeUtils::Double ||
            type == SnakeUtils::UDouble;
}

bool SnakeUtils::isString(SnakeUtils::Type type) {
    return type == SnakeUtils::String;
}

bool SnakeUtils::isArray(SnakeUtils::Type type) {
    return type & SnakeUtils::Array;
}

bool SnakeUtils::isVariant(SnakeUtils::Type type) {
    return type == SnakeUtils::Variant;
}

int SnakeUtils::getSizeType(SnakeUtils::Type type) {
    switch (type) {
    case SnakeUtils::Char:
    case SnakeUtils::UChar: return sizeof (char);
    case SnakeUtils::Short:
    case SnakeUtils::UShort: return sizeof(short);
    case SnakeUtils::Int:
    case SnakeUtils::UInt: return sizeof(int);
    case SnakeUtils::Float:
    case SnakeUtils::UFloat: return sizeof (float);
    case SnakeUtils::Double:
    case SnakeUtils::UDouble: return sizeof (double);
    case SnakeUtils::SHA256: return 32;
    default: return 0;
    }
}

SnakeUtils::SnakeUtils()
{
}

