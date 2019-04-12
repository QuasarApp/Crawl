#ifndef SQLDATABASE_H
#define SQLDATABASE_H
#include <QObject>
#include <QSqlDatabase>

#define DEFAULT_DB_NAME "SnakeDatabase.db"
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
    bool initDb(const QString &sql = DEFAULT_DB_NAME);
    bool isValid() const;

    bool getItem(int id, QVariantMap &res) const;
    bool saveItem(const QVariantMap &item);

    bool getPlayer(int id, QVariantMap &res) const;
    bool savePlayer(const QVariantMap &player);

    bool isValidItem(const QVariantMap& item, int idItem, QByteArray tocken);
    bool isValidPlayer(const QVariantMap& player);
    bool isValidMap(const QVariantMap& map);

};

#endif // SQLDATABASE_H
