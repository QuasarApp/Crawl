#include "networkobjects.h"

const QHash<SnakeUtils::Type, QMap<QString, SnakeUtils::Type>> networkObjects = {
    {SnakeUtils::Type::Snake, {
         {"spead", SnakeUtils::UChar},
         {"class", SnakeUtils::UChar},
         {"skillet", SnakeUtils::ArrayFloat}
     }
    },
    {SnakeUtils::Type::Player, {
         {"token", SnakeUtils::SHA256},
         {"name", SnakeUtils::String},
         {"gmail", SnakeUtils::String},
         {"maney", SnakeUtils::UInt},
         {"record", SnakeUtils::UInt},
         {"items", SnakeUtils::ArrayUInt},
         {"currentSnake", SnakeUtils::UInt}
     }
    },
    {SnakeUtils::Type::Map, {
         {"lvl", SnakeUtils::UChar},
         {"long", SnakeUtils::UShort},
         {"listObj", SnakeUtils::ArrayUChar},
         {"xObj", SnakeUtils::ArrayUShort},
         {"yObj", SnakeUtils::ArrayUShort},
         {"ratObj", SnakeUtils::ArrayUShort}
     }
    },
    {SnakeUtils::Type::Game, {
         {"token", SnakeUtils::SHA256},
         {"time", SnakeUtils::ArrayInt}
     }
    }
};
