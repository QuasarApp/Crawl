#include "sqldatabase.h"

#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QRegularExpression>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextStream>
#include <quasarapp.h>
#include <QSqlError>
#include <QDir>

#include <networkclasses.h>
#include <clientprotocol.h>
#include <streamers.h>
#include <qdebug.h>
#include <QDateTime>
#include <QThread>
#include <QFuture>
#include <qtconcurrentrun.h>


bool SQLDataBase::exec(QSqlQuery *sq,const QString& sqlFile) {
    QFile f(sqlFile);
    bool result = true;
    if (f.open(QIODevice::ReadOnly)) {

        QString temp, delimiter = ";";
        QTextStream stream(&f);
        stream.setCodec("UTF8");

        while(!stream.atEnd()) {
            temp += stream.readLine();
            if (temp.lastIndexOf("delimiter", -1, Qt::CaseInsensitive) > -1) {
                temp.remove("delimiter", Qt::CaseInsensitive);
                int last = temp.indexOf(QRegularExpression("[^ \f\n\r\t\v]")) + 1;
                int begin = temp.lastIndexOf(QRegularExpression("[^ \f\n\r\t\v]"));
                delimiter = temp.mid(begin, last - begin);
                temp = "";
            } else {
                if (temp.lastIndexOf(delimiter) >- 1) {
                    temp.remove(delimiter);
                    result = result && sq->exec(temp);

                    if (!result) {
                        qCritical() << sq->lastError().text();
                        f.close();
                        return false;
                    }

                    temp = "";
                }
            }
        }

        f.close();
        return result;
    }
    return false;
}

int SQLDataBase::getPlayerId(const QString &gmail) {

    QString request = QString("SELECT id from players where gmail='%0'").arg(gmail);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    if (!query->next()) {
        return -1;
    }

    return query->value("id").toInt();
}

bool SQLDataBase::initIdItems() {
    items.clear();

    QString request = QString("SELECT id FROM items");
    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    while (query->next()) {
        items.insert(query->value(0).toInt(), QVariantMap());
    }

    return true;
}

bool SQLDataBase::initIdPlayers() {
    players.clear();

    QString request = QString("SELECT id FROM players");
    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    while (query->next()) {
        players.insert(query->value(0).toInt(), QVariantMap());
    }

    return true;
}

int SQLDataBase::generateIdForItem() const{
    if (items.isEmpty()) {
        return 0;
    }

    return items.lastKey() + 1;
}

int SQLDataBase::generateIdForPalyer() const {
    if (items.isEmpty()) {
        return 0;
    }

    return items.lastKey() + 1;
}

bool SQLDataBase::checkPlayer(int id) const {

    if (players.contains(id)) {
        return true;
    }

    QString request = QString("SELECT id from players where id='%0'").arg(id);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    if (!query->next()) {
        return false;
    }

    return true;
}

bool SQLDataBase::checkItem(int idItem, int idOwner) const {

    if (idOwner >= 0 ) {
        if (!checkPlayer(idOwner)) {
            return false;
        }

        if (owners.value(idOwner).contains(idItem)) {
            return true;
        }

        QString request = QString("SELECT item from ovners where player='%0' and item='%1'").
                arg(idOwner).arg(idItem);

        if (!query->exec(request)) {
            QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
            return false;
        }

        if (!query->next()) {
            return false;
        }

        return true;
    }

    if (items.contains(idItem)) {
        return true;
    }

    QString request = QString("SELECT item from items where id='%0'").
            arg(idItem);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    if (!query->next()) {
        return false;
    }

    return true;
}

int SQLDataBase::writeUpdatePlayerIntoDB(const QVariantMap &player) const {
    QString request;
    int id = player.value("id").toInt();
    if (id < 0) {
         request = QString("INSERT INTO players(id, name, gmail, money, avgrecord, record,"
                                  " lastOnline, onlinetime, currentsnake) VALUES "
                                  "('%0', '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')").arg(
                        player.value("id").toString(),
                        player.value("name").toString(),
                        player.value("money").toString(),
                        player.value("avgrecord").toString(),
                        player.value("record").toString(),
                        player.value("lastOnline").toString(),
                        player.value("onlinetime").toString(),
                        player.value("currentsnake").toString());
    } else {
        id = generateIdForPalyer();
        request = QString("UPDATE players SET name='%0', gmail='%1', money='%2',"
                          " avgrecord='%3', record='%4', lastOnline='%5',"
                          " onlinetime='%6', currentsnake='%7') WHERE id='%8' ").arg(
                        player.value("name").toString(),
                        player.value("money").toString(),
                        player.value("avgrecord").toString(),
                        player.value("record").toString(),
                        player.value("lastOnline").toString(),
                        player.value("onlinetime").toString(),
                        player.value("currentsnake").toString(),
                        QString::number(id));
    }


    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    return true;
}

int SQLDataBase::writeUpdateItemIntoDB(const QVariantMap &item) const {
    auto type = static_cast<ClientProtocol::NetworkClasses::Type>
            (item.value("command", ClientProtocol::NetworkClasses::Undefined).toInt());

    int id = item.value("id", -1).toInt();

    QByteArray bytes;
    QString request;

    if (!ClientProtocol::Streamers::write(bytes, item)) {
        return -1;
    }

    if (id < 0) {
        id = generateIdForItem();

        request = QString("INSERT INTO items(id,type,data) VALUES "
                                  "('%0', '%1', ':bytes')").
                arg(id).
                arg(static_cast<int>(type));
    } else {

        request = QString("UPDATE items SET type='%1', data=':bytes' where id = %0").
                arg(id).
                arg(static_cast<int>(type));
    }


    query->bindValue( ":bytes", bytes);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    return id;
}

bool SQLDataBase::getAllItemsOfPalyerFromDB(int player, QSet<int> &items) {
    QString request = QString("SELECT item from owners where player='%0'").arg(player);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    while (query->next()) {
        items.insert(query->value(0).toInt());
    }

    return true;
}

void SQLDataBase::globalUpdateDataBasePrivate(qint64 currentTime)
{
    QList<int> removeIds;
    for (auto item = items.begin(); item != items.end(); ++item) {
        if (writeUpdateItemIntoDB(item.value()) < 0) {
            removeIds.push_back(item.key());
            qCritical() << "writeUpdateItemIntoDB failed when"
                           " work globalUpdateDataRelease!!! id=" << item.key();
        }
    }

    for (int id : removeIds) {
        items.remove(id);
    }

    for (auto player = players.begin(); player != players.end(); ++player) {
        if (writeUpdatePlayerIntoDB(player.value()) < 0) {
            removeIds.push_back(player.key());
            qCritical() << "writeUpdatePlayerIntoDB failed when"
                           " work globalUpdateDataRelease!!! id=" << player.key();
        }
    }

    for (auto owner = owners.begin(); owner != owners.end(); ++owner) {
        if (UpdateInfoOfOvners(owner.key(), owner.value())) {
            qCritical() << "UpdateInfoOfOvners failed when"
                           " work globalUpdateDataRelease!!! id=" << owner.key();
        }
    }

    lastUpdateTime = currentTime;
}

void SQLDataBase::globalUpdateDataBase(bool force) {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    if (currentTime - lastUpdateTime > DEFAULT_UPDATE_INTERVAL || force) {
        QtConcurrent::run([currentTime, this](){
            globalUpdateDataBasePrivate(currentTime);
        });
    }
}

bool SQLDataBase::itemIsFreeFromCache(int item) const{
    for (auto &owner : owners) {
        if (owner.contains(item)) {
            return false;
        }
    }

    return true;
}

bool SQLDataBase::UpdateInfoOfOvners(int player, const QSet<int> items) {

    QString request = QString("DELETE from owners where player='%0' ").
            arg(player).arg(player);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    request = QString("INSERT INTO owners(player, items) VALUES(");
    for (int item: items) {
        request.push_back("(" + QString::number(player) + "," + QString::number(item) + ")");
    }

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog(request);
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    return true;
}

SQLDataBase::SQLDataBase(QObject *ptr): QObject (ptr) {
    dbThread = new QThread();
}

bool SQLDataBase::initDb(const QString& database, const QString &databasePath) {
    QStringList drivers = QSqlDatabase::drivers();
    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLITE", database);

    db->setDatabaseName(QFileInfo(databasePath).absolutePath() + "/" + database);
    query = new QSqlQuery(*db);

    if (!db->open()) {
        return false;
    }

    if (!exec(query, ":/sql/DB")) {
        return false;
    }

    initSuccessful = initIdItems() && initIdPlayers();
    return initSuccessful;
}

bool SQLDataBase::isValid() const {
    if (!db) {
        return false;
    }

    return db->isValid() && db->isOpen() && initSuccessful;
}

bool SQLDataBase::getItem(int id, QVariantMap &res) const {

    if (!isValid()) {
        return false;
    }

    auto itemCondidate = items.value(id);
    if (itemCondidate.size()) {
        res = itemCondidate;
        return true;
    }

    QString request = QString("SELECT data FROM items WHERE id=%0").arg(id);
    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    if (!query->next()) {
        return false;
    }
    auto data = query->value(0).toByteArray();

    return ClientProtocol::Streamers::read(data, res);
}

int SQLDataBase::saveItem(QVariantMap &item) {

    if (!isValid()) {
        return -1;
    }

    if (!ClientProtocol::isValidMap(item)) {
        return false;
    }

    int id = item.value("id", -1).toInt();
    if (id < 0) {
        id = writeUpdateItemIntoDB(item);
        item.insert("id", id);
    }

    items.insert(id, item);

    globalUpdateDataBase();

    return true;
}

bool SQLDataBase::getPlayer(int id, QVariantMap &res) const {

    if (!isValid()) {
        return false;
    }

    QString request = QString("SELECT * FROM players WHERE id=%0").arg(id);
    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    if (!query->next()) {
        return false;
    }
    res["name"] = query->value("name");
    res["gmail"] = query->value("gmail");
    res["money"] = query->value("money");
    res["avgrecord"] = query->value("avgrecord");
    res["record"] = query->value("record");
    res["lastOnline"] = query->value("lastOnline");
    res["onlinetime"] = query->value("onlinetime");
    res["currentsnake"] = query->value("currentsnake");

    return true;
}

int SQLDataBase::savePlayer( QVariantMap &player) {

    if (!isValid()) {
        return -1;
    }

    if (!ClientProtocol::isValidMap(player)) {
        return -1;
    }

    int id = player.value("id", -1).toInt();
    if (id < 0) {
        id = writeUpdatePlayerIntoDB(player);
        player.insert("id", id);
    }

    players.insert(id, player);

    globalUpdateDataBase();

    return true;
}

bool SQLDataBase::giveAwayItem(int player, int item) {

    if (!isValid()) {
        return false;
    }

    if (!(checkPlayer(player) && checkItem(item, player))) {
        return false;
    }

    if (owners.contains(player)) {
        auto &owner = owners[player];
        return owner.remove(item);
    }

    QString request = QString("DELETE from owners where player='%0' and item='%1'").
            arg(player).arg(item);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    QSet<int> items;
    if (!getAllItemsOfPalyerFromDB(player, items)) {
        return false;
    }

    owners.insert(player, items);

    return true;
}

bool SQLDataBase::getItem(int player, int item, bool check) {

    if (!isValid()) {
        return false;
    }

    if (!(checkPlayer(player) && checkItem(item))) {
        return false;
    }

    if (owners.contains(player) && (!check || itemIsFreeFromCache(item))) {
        auto &owner = owners[player];
        owner.insert(item);
        return true;
    }

    QString request = QString("INSERT INTO owners (player, item)"
                              " VALUES(player='%0', item='%1')").
            arg(player).arg(item);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }


    QSet<int> items;
    if (!getAllItemsOfPalyerFromDB(player, items)) {
        return false;
    }

    owners.insert(player, items);

    return true;
}

bool SQLDataBase::moveItem(int owner, int receiver, int item) {
    return giveAwayItem(owner, item) && getItem(receiver, item, false);
}

bool SQLDataBase::getAllItemsOfPalyer(int player, QSet<int> &items) {
    if (owners.contains(player)) {
        items = owners.value(player);
        return true;
    }

    return getAllItemsOfPalyerFromDB(player, items);
}

SQLDataBase::~SQLDataBase() {

    globalUpdateDataBase();

    if (db) {
        delete db;
    }

    if (query) {
        delete query;
    }
}

