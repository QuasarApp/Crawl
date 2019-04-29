#include "playerdbdata.h"
#include "sqldbwriter.h"

#include <QRegularExpression>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <quasarapp.h>
#include <clientprotocol.h>
#include <factorynetobjects.h>

bool SqlDBWriter::exec(QSqlQuery *sq,const QString& sqlFile) {
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

int SqlDBWriter::getLastIdItems() {
    if (!isValid()) {
        return -1;
    }

    QString request = QString("SELECT MAX(id) FROM items");
    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return -1;
    }

    if (!query->next()) {
        return -1;
    }

    return query->value(0).toInt();
}

int SqlDBWriter::getLastIdPlayers() {
    if (!isValid()) {
        return -1;
    }

    QString request = QString("SELECT MAX(id) FROM players");
    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return -1;
    }

    if (!query->next()) {
        return -1;
    }

    return query->value(0).toInt();
}

int SqlDBWriter::getPlayerId(const QString &gmail) {

    if (!isValid()) {
        return -1;
    }

    QString request = QString("SELECT id from players where gmail='%0'").arg(gmail);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return -1;
    }

    if (!query->next()) {
        return -1;
    }

    return query->value("id").toInt();
}

bool SqlDBWriter::checkPlayer(int id) {

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

bool SqlDBWriter::checkItem(int idItem, int idOwner) {


    if (idOwner >= 0 ) {
        if (!checkPlayer(idOwner)) {
            return false;
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

    QString request = QString("SELECT id from items where id='%0'").
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

int SqlDBWriter::savePlayer(PlayerDBData *player) {
    if (!isValid()) {
        return -1;
    }

    if (!player->isValid()) {
        return -1;
    }

    QString request;
    int id = player->id();

    if (checkPlayer(id)) {
        request = QString("UPDATE players SET name='%0', gmail='%1', money='%2',"
                          " avgrecord='%3', record='%4', lastOnline='%5',"
                          " onlinetime='%6', currentsnake='%7') WHERE id='%8' ").arg(
                        player->getName()).arg(
                        player->getGmail()).arg(
                        player->getMany()).arg(
                        player->getAvgRecord()).arg(
                        player->getRecord()).arg(
                        player->getLastOnline()).arg(
                        player->getOnlineTime()).arg(
                        player->getCureentSnake()).arg(
                        QString::number(id));

    } else {
        request = QString("INSERT INTO players(id, name, gmail, money, avgrecord, record,"
                                 " lastOnline, onlinetime, currentsnake) VALUES "
                                 "('%0', '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')").arg(
                       id).arg(
                    player->getName()).arg(
                    player->getGmail()).arg(
                    player->getMany()).arg(
                    player->getAvgRecord()).arg(
                    player->getRecord()).arg(
                    player->getLastOnline()).arg(
                    player->getOnlineTime()).arg(
                    player->getCureentSnake());

    }


    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    return id;
}

int SqlDBWriter::saveItem(ClientProtocol::BaseNetworkObject *item) {
    if (!isValid()) {
        return -1;
    }

    if (item->isValid()) {
        return -1;
    }

    auto type = item->getClass();

    int id = item->id();

    QByteArray bytes;
    QString request;

    item->toBytes(bytes);

    if (checkItem(id)) {
        request = QString("UPDATE items SET type='%1', data = :bytes where id = %0").
                arg(id).
                arg(static_cast<int>(type));
    } else {
        request = QString("INSERT INTO items(id, type, data) VALUES"
                                  "('%0', '%1', :bytes)").
                arg(id).
                arg(static_cast<int>(type));
    }

    if (!query->prepare(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return -1;
    }

    query->bindValue(":bytes", bytes);

    if (!query->exec()) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return -1;
    }

    return id;
}

bool SqlDBWriter::getAllItemsOfPalyer(int player, QSet<int> &items) {
    if (!isValid()) {
        return false;
    }

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

bool SqlDBWriter::saveOvners(int player, const QSet<int> items) {

    if (!isValid()) {
        return false;
    }

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

PlayerDBData * SqlDBWriter::getPlayer(int id) {

    if (!isValid()) {
        return nullptr;
    }

    QString request = QString("SELECT * FROM players WHERE id=%0").arg(id);
    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return nullptr;
    }

    if (!query->next()) {
        return nullptr;
    }

    auto player = new PlayerDBData();


    player->setName(query->value("name").toString());
    player->setGmail(query->value("gmail").toString());
    player->setMany(query->value("money").toUInt());
    player->setAvgRecord(query->value("avgrecord").toUInt());
    player->setRecord(query->value("record").toUInt());
    player->setLastOnline(query->value("lastOnline").toInt());
    player->setOnlineTime(query->value("onlinetime").toInt());
    player->setCureentSnake(query->value("currentsnake").toInt());

    return player;
}

ClientProtocol::BaseNetworkObject *SqlDBWriter::getItem(int id) {

    if (!isValid()) {
        return nullptr;
    }

    QString request = QString("SELECT type, data FROM items WHERE id=%0").arg(id);
    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return nullptr;
    }

    if (!query->next()) {
        return nullptr;
    }

    auto type = static_cast<quint8>(query->value(1).toUInt());
    auto data = query->value(1).toByteArray();

    auto obj = ClientProtocol::FactoryNetObjects::build(type);

    if (!obj)
        return nullptr;

    obj->fromBytes(data);

    return obj;
}

bool SqlDBWriter::itemIsFreeFrom(int item) const {
    if (!isValid()) {
        return false;
    }

    QString request = QString("SELECT player FROM owners WHERE id=%0").arg(item);
    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    return !query->next();
}

SqlDBWriter::SqlDBWriter() {

}

bool SqlDBWriter::initDb(const QString& database, const QString &databasePath) {
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

    initSuccessful = true;
    return initSuccessful;
}

bool SqlDBWriter::isValid() const {
    if (!db) {
        return false;
    }

    return db->isValid() && db->isOpen() && initSuccessful;
}

SqlDBWriter::~SqlDBWriter() {
    if (db) {
        delete db;
    }

    if (query) {
        delete query;
    }
}
