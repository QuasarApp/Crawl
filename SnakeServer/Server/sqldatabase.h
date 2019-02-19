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
public:
    SQLDataBase(QObject * ptr = nullptr);
    bool initDb(const QString &sql = DEFAULT_DB_NAME);

    QVariantMap getItem(int id) const;
    bool isValidItem(const QVariantMap& player, int idItem, QByteArray tocken);
    bool isValidPlayer(const QVariantMap& player);
    bool isValidMap(const QVariantMap& map);

};

#endif // SQLDATABASE_H
