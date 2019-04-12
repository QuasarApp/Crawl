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
#include <streamers.h>

SQLDataBase::SQLDataBase(QObject *ptr):
    QObject (ptr) {
}

bool SQLDataBase::exec(QSqlQuery *sq,const QString& sqlFile){
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
                    temp = "";
                }
            }
        }
        return result;
    }
    return false;
}

bool SQLDataBase::ifExistItem(int id) {
    QString request = QString("SELECT id from items where id='%0'").arg(id);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    return query->next();
}

bool SQLDataBase::existPlayer(int id) {
    QString request = QString("SELECT id from players where id='%0'").arg(id);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    return query->next();
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

bool SQLDataBase::initDb(const QString& database, const QString &databasePath) {
    QStringList drivers = QSqlDatabase::drivers();
    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLITE", database);

    db->setDatabaseName(QFileInfo(databasePath).absolutePath() + database);
    query = new QSqlQuery(*db);

    if (!db->open()) {
        return false;
    }

    if (!exec(query, ":/sql/DB")) {
        return false;
    }

    return true;
}

bool SQLDataBase::isValid() const {
    if (!db) {
        return false;
    }

    return db->isValid() && db->isOpen();
}

bool SQLDataBase::getItem(int id, QVariantMap &res) const {
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

bool SQLDataBase::saveItem(const QVariantMap &item) {
    auto type = static_cast<ClientProtocol::NetworkClasses::Type>
            (item.value("command", ClientProtocol::NetworkClasses::Undefined).toInt());

    if (!ClientProtocol::NetworkClasses::isCustomType(type)) {
        return false;
    }

    QByteArray bytes;
    if (!ClientProtocol::Streamers::write(bytes, item)) {
        return false;
    }

    QString request = QString("SINSERT INTO items(type,data) VALUES "
                              "('%0', :bytes)").arg(static_cast<int>(type));

    query->bindValue( ":bytes", bytes);

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return false;
    }

    return true;
}

bool SQLDataBase::getPlayer(const QString& gmail, QVariantMap &res) const {
    QString request = QString("SELECT * FROM players WHERE gmail=%0").arg(gmail);
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

bool SQLDataBase::getPlayer(int id, QVariantMap &res) const {
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

bool SQLDataBase::savePlayer(const QVariantMap &player){
    QString request;
    int id = getPlayerId(player.value("gmail").toString());
    if (id < 0) {
         request = QString("INSERT INTO players(name, gmail, money, avgrecord, record,"
                                  " lastOnline, onlinetime, currentsnake) VALUES "
                                  "('%0', '%1', '%2', '%3', '%4', '%5', '%6', '%7')").arg(
                        player.value("name").toString(),
                        player.value("money").toString(),
                        player.value("avgrecord").toString(),
                        player.value("record").toString(),
                        player.value("lastOnline").toString(),
                        player.value("onlinetime").toString(),
                        player.value("currentsnake").toString());
    } else {
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

