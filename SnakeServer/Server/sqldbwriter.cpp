#include "sqldbwriter.h"

#include <QRegularExpression>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <quasarapp.h>
#include <clientprotocol.h>
#include <streamers.h>
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

int SqlDBWriter::savePlayer(QVariantMap &player) {
    if (!isValid()) {
        return -1;
    }

    if (!ClientProtocol::FactoryNetObjects::isValid(player,
            ClientProtocol::NetworkClasses::Player)) {
        return -1;
    }

    QString request;
    int id = player.value("id").toInt();

    if (id < 0) {
        return -1;
    }

    if (checkPlayer(id)) {
        request = QString("UPDATE players SET name='%0', gmail='%1', money='%2',"
                          " avgrecord='%3', record='%4', lastOnline='%5',"
                          " onlinetime='%6', currentsnake='%7') WHERE id='%8' ").arg(
                        player.value("name").toString(),
                        player.value("gmail").toString(),
                        player.value("money").toString(),
                        player.value("avgrecord").toString(),
                        player.value("record").toString(),
                        player.value("lastOnline").toString(),
                        player.value("onlinetime").toString(),
                        player.value("currentsnake").toString(),
                        QString::number(id));

    } else {
        request = QString("INSERT INTO players(id, name, gmail, money, avgrecord, record,"
                                 " lastOnline, onlinetime, currentsnake) VALUES "
                                 "('%0', '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')").arg(
                       player.value("id").toString(),
                       player.value("name").toString(),
                       player.value("gmail").toString(),
                       player.value("money").toString(),
                       player.value("avgrecord").toString(),
                       player.value("record").toString(),
                       player.value("lastOnline").toString(),
                       player.value("onlinetime").toString(),
                       player.value("currentsnake").toString());


    }


    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    return id;
}

int SqlDBWriter::saveItem(QVariantMap &item) {
    if (!isValid()) {
        return -1;
    }

    if (ClientProtocol::FactoryNetObjects::isValid(item,
            ClientProtocol::NetworkClasses::Player)) {
        return -1;
    }

    auto type = static_cast<ClientProtocol::NetworkClasses::Type>
            (item.value("command", ClientProtocol::NetworkClasses::Undefined).toInt());

    int id = item.value("id", -1).toInt();

    if (id < 0) {
        return -1;
    }

    QByteArray bytes;
    QString request;

    if (!ClientProtocol::Streamers::write(bytes, item)) {
        return -1;
    }

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

bool SqlDBWriter::getPlayer(int id, QVariantMap &res) {

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

bool SqlDBWriter::getItem(int id, QVariantMap &res) {

    if (!isValid()) {
        return false;
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
