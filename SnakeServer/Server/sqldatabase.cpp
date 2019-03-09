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

QVariantMap SQLDataBase::getItem(int id) const {
    QString request = QString("SELECT type,data WHERE id=%0").arg(id);

    QVariantMap res;

    if (!query->exec(request)) {
        QuasarAppUtils::Params::verboseLog("request error : " + query->lastError().text());
        return res;
    }

    return res;
}

