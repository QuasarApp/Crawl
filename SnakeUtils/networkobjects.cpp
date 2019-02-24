#include "networkobjects.h"

const QHash<SnakeUtils::Type, QMap<QString, SnakeUtils::Type>> networkObjects = {
    {SnakeUtils::Type::Snake, {
         {"spead", SnakeUtils::UChar},
         {"class", SnakeUtils::UChar},
         {"skillet", SnakeUtils::ArrayFloat}
     }
    },
    {SnakeUtils::Type::Player, {
         {"name", SnakeUtils::String},
         {"gmail", SnakeUtils::String},
         {"maney", SnakeUtils::UInt},
         {"record", SnakeUtils::UInt},
         {"items", SnakeUtils::ArrayUInt},
         {"currentSnake", SnakeUtils::UInt}
     }
    }
};
