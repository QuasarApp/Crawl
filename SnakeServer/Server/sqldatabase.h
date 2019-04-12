#ifndef SQLDATABASE_H
#define SQLDATABASE_H
#include <QObject>
#include <QSqlDatabase>
#include <QDir>

#define DEFAULT_DB_NAME "SnakeDatabase.db"
#define DEFAULT_DB_PATH QDir::homePath() + "/SnakeServer"


class QSqlQuery;
class QSqlDatabase;
class QSqlQuery;

class SQLDataBase : public QObject
{
    Q_OBJECT
private:

    bool exec(QSqlQuery *sq, const QString &sqlFile);
    QSqlDatabase *db = nullptr;
    QSqlQuery *query = nullptr;

    bool ifExistItem(int id);
    bool existPlayer(int id);
    int getPlayerId(const QString &id);

public:
    SQLDataBase(QObject * ptr = nullptr);
    bool initDb(const QString &sql = DEFAULT_DB_NAME,
                const QString &path = DEFAULT_DB_PATH);
    bool isValid() const;

    bool getItem(int id, QVariantMap &res) const;
    bool saveItem(const QVariantMap &item);

    bool getPlayer(int id, QVariantMap &res) const;
    bool getPlayer(const QString& gmail, QVariantMap &res) const;

    bool savePlayer(const QVariantMap &player);

    friend class testSankeServer;
};

#endif // SQLDATABASE_H
