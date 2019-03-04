#include "networkobjects.h"

namespace ClientProtocol {

const QHash<NetworkClasses::Type, QMap<QString, NetworkClasses::Type>> networkObjects = {
    {NetworkClasses::Type::Ping, {}
    },
    {NetworkClasses::Type::Snake, {
         {"spead", NetworkClasses::UChar},
         {"class", NetworkClasses::UChar},
         {"skillet", NetworkClasses::ArrayFloat}
     }
    },
    {NetworkClasses::Type::Player, {
         {"token", NetworkClasses::SHA256},
         {"name", NetworkClasses::String},
         {"gmail", NetworkClasses::String},
         {"maney", NetworkClasses::UInt},
         {"record", NetworkClasses::UInt},
         {"items", NetworkClasses::ArrayUInt},
         {"currentSnake", NetworkClasses::UInt}
     }
    },
    {NetworkClasses::Type::Login, {
         {"gmail", NetworkClasses::String},
         {"hashPass", NetworkClasses::SHA256}
     }
    },
    {NetworkClasses::Type::UpdatePlayerData, {
         {"token", NetworkClasses::SHA256}
     }
    },
    {NetworkClasses::Type::Map, {
         {"lvl", NetworkClasses::UChar},
         {"long", NetworkClasses::UShort},
         {"listObj", NetworkClasses::ArrayUChar},
         {"xObj", NetworkClasses::ArrayUShort},
         {"yObj", NetworkClasses::ArrayUShort},
         {"ratObj", NetworkClasses::ArrayUShort}
     }
    },
    {NetworkClasses::Type::Game, {
         {"token", NetworkClasses::SHA256},
         {"time", NetworkClasses::ArrayInt}
     }
    },
    {NetworkClasses::Type::GetItem, {
         {"token", NetworkClasses::SHA256},
         {"id", NetworkClasses::Int}
     }
    }
};

}
