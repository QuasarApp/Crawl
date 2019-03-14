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

bool SQLDataBase::initDb(const QString& database) {
    QStringList drivers = QSqlDatabase::drivers();
    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLITE", database);

    auto exePath = QuasarAppUtils::Params::getArg("appPath").toString();

    db->setDatabaseName(QFileInfo(exePath).absolutePath() + database);
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

bool SQLDataBase::saveItem(const QVariantMap &item) const {
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

