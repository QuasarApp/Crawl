#include "sqldbcashe.h"
#include "quasarapp.h"
#include <qtconcurrentrun.h>
#include <clientprotocol.h>

#include <QDateTime>

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

bool SqlDBCashe::checkPlayer(int id) {
    if (players.contains(id)) {
        return true;
    }

    if (SqlDBWriter::checkPlayer(id)) {

        QVariantMap player;
        getPlayer(id, player);
        if (savePlayer(player) < 0) {
            QuasarAppUtils::Params::verboseLog("not saved data into cache "
                                               " SqlDBCashe::checkPlayer");
        }

        return true;
    }

    return false;
}

bool SqlDBCashe::checkItem(int idItem, int idOwner) {

    if (idOwner >= 0 ) {

        if (owners.contains(idOwner)) {
            auto items = owners.value(idOwner);
            return items.contains(idItem);
        }

        if (SqlDBWriter::checkItem(idItem)) {
            QSet<int> items;
            if (!SqlDBWriter::getAllItemsOfPalyer(idOwner, items)) {
                QuasarAppUtils::Params::verboseLog("not loaded ovners data from cache "
                                                   " SqlDBCashe::checkItem");
            }

            owners.insert(idOwner, items);

            return true;
        }

        return false;

    }

    if (items.contains(idItem)) {
        return true;
    }

    if (SqlDBWriter::checkItem(idItem)) {

        QVariantMap item;
        getItem(idItem, item);
        if (saveItem(item) < 0) {
            QuasarAppUtils::Params::verboseLog("not saved data into cache "
                                               " SqlDBCashe::checkItem");
        }

        return true;
    }

    return false;
}

void SqlDBCashe::globalUpdateDataBasePrivate(qint64 currentTime) {
    QList<int> removeIds;
    for (auto item = items.begin(); item != items.end(); ++item) {
        if (SqlDBWriter::saveItem(item.value()) < 0) {
            removeIds.push_back(item.key());

            QuasarAppUtils::Params::verboseLog("writeUpdateItemIntoDB failed when"
                                               " work globalUpdateDataRelease!!! id=" +
                                                QString::number(item.key()));
        }
    }

    for (int id : removeIds) {
        items.remove(id);
    }

    for (auto player = players.begin(); player != players.end(); ++player) {
        if (savePlayer(player.value()) < 0) {
            removeIds.push_back(player.key());
            QuasarAppUtils::Params::verboseLog("writeUpdatePlayerIntoDB failed when"
                                               " work globalUpdateDataRelease!!! id=" +
                                                QString::number(player.key()));

        }
    }

    for (auto owner = owners.begin(); owner != owners.end(); ++owner) {
        if (saveOvners(owner.key(), owner.value())) {
            QuasarAppUtils::Params::verboseLog("UpdateInfoOfOvners failed when"
                                               " work globalUpdateDataRelease!!! id=" +
                                                QString::number(owner.key()));
        }
    }

    lastUpdateTime = currentTime;
}

void SqlDBCashe::globalUpdateDataBase(SqlDBCasheWriteMode mode) {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    if (currentTime - lastUpdateTime > DEFAULT_UPDATE_INTERVAL ||
            static_cast<bool>(mode & SqlDBCasheWriteMode::Force)) {

        if (static_cast<bool>(mode & SqlDBCasheWriteMode::On_New_Thread)) {

            QtConcurrent::run([currentTime, this](){
                globalUpdateDataBasePrivate(currentTime);
            });

        } else {
            globalUpdateDataBasePrivate(currentTime);
        }
    }
}

bool SqlDBCashe::itemIsFreeFrom(int item) const {
    return SqlDBWriter::itemIsFreeFrom(item);
}

SqlDBCashe::SqlDBCashe() {
}

SqlDBCashe::~SqlDBCashe() {
    globalUpdateDataBase(SqlDBCasheWriteMode::Force);
}

bool SqlDBCashe::initDb(const QString &sql, const QString &path) {
    if (!SqlDBWriter::initDb(sql, path)) {
        return false;
    }

    QVariantMap temp;
    if (int id = getLastIdItems()) {
        getItem(id, temp);
    }

    if (int id = getLastIdPlayers()) {
        getPlayer(id, temp);
    }

    return true;
}

bool SqlDBCashe::getItem(int id, QVariantMap &res) {
    auto item = items.value(id, QVariantMap{{"id", "-1"}});
    if (item.value("id") != "-1") {
        res = item;
        return true;
    }

    if (SqlDBWriter::getItem(id, res)) {
        items.insert(id, res);
        return true;
    }

    return false;
}

int SqlDBCashe::saveItem(QVariantMap &item) {

    if (!ClientProtocol::isValidMap(item)) {
        return -1;
    }

    int id = item.value("id", -1).toInt();

    if (id < 0) {
        id = generateIdForItem();
        item.insert("id", id);
    }

    items.insert(id, item);

    globalUpdateDataBase(SqlDBCasheWriteMode::On_New_Thread);

    return id;
}

bool SqlDBCashe::getPlayer(int id, QVariantMap &res) {
    auto player = players.value(id, QVariantMap{{"id", "-1"}});
    if (player.value("id") != "-1") {
        res = player;
        return true;
    }

    if (SqlDBWriter::getPlayer(id, res)) {
        players.insert(id, res);
        return true;
    }

    return false;
}

int SqlDBCashe::savePlayer(QVariantMap &player) {
    if (!ClientProtocol::isValidMap(player)) {
        return -1;
    }

    int id = player.value("id", -1).toInt();

    if (id < 0) {
        id = generateIdForItem();
        player.insert("id", id);
    }

    players.insert(id, player);

    globalUpdateDataBase(SqlDBCasheWriteMode::On_New_Thread);

    return id;
}

bool SqlDBCashe::giveAwayItem(int player, int item) {
    if (!isValid()) {
        return false;
    }

    if (!checkItem(item, player)) {
        return false;
    }

    if (owners.contains(player)) {
        auto &owner = owners[player];
        owner.remove(item);

        globalUpdateDataBase(SqlDBCasheWriteMode::On_New_Thread);

        return true;
    }

    return false;
}

bool SqlDBCashe::getItem(int player, int item, bool check) {
    if (!isValid()) {
        return false;
    }

    if (!(checkPlayer(player) && checkItem(item))) {
        return false;
    }

    if (check && !itemIsFreeFrom(item)) {
        return false;
    }

    if (owners.contains(player)) {
        auto &owner = owners[player];
        owner.insert(item);

        globalUpdateDataBase(SqlDBCasheWriteMode::On_New_Thread);

        return true;
    }

    QSet<int> items;
    if (!getAllItemsOfPalyer(player, items)) {
        return false;
    }

    if (owners.contains(player)) {
        auto &owner = owners[player];
        owner.insert(item);

        globalUpdateDataBase(SqlDBCasheWriteMode::On_New_Thread);

        return true;
    }

    return false;
}

bool SqlDBCashe::moveItem(int owner, int receiver, int item) {
    return giveAwayItem(owner, item) && getItem(receiver, item, false);
}

bool SqlDBCashe::getAllItemsOfPalyer(int player, QSet<int> &items) {
    if (owners.contains(player)) {
        items = owners[player];
        return true;
    }

    if (SqlDBWriter::getAllItemsOfPalyer(player, items) &&
            checkPlayer(player)) {

        owners.insert(player, items);
        return true;
    }

    return false;
}
