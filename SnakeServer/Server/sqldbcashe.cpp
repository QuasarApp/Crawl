#include "sqldbcashe.h"

int SqlDBCashe::generateIdForItem() const {
    if (items.isEmpty()) {
        return 0;
    }

    return items.lastKey() + 1;
}

int SqlDBCashe::generateIdForPalyer() const {
    if (players.isEmpty()) {
        return 0;
    }

    return players.lastKey() + 1;
}

bool SqlDBCashe::checkPlayer(int id) const {

}

bool SqlDBCashe::checkItem(int idItem, int idOwner) const {

}

SqlDBCashe::SqlDBCashe()
{

}
