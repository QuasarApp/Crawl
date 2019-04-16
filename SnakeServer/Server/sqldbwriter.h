#ifndef SQLDBWRITER_H
#define SQLDBWRITER_H
#include <QObject>
#include <QSqlDatabase>
#include <QDir>

#define DEFAULT_DB_NAME "SnakeDatabase.db"
#define DEFAULT_DB_PATH QDir::homePath() + "/SnakeServer"
#define DEFAULT_UPDATE_INTERVAL 3600000 // 1 hour

class QSqlQuery;
class QSqlDatabase;
class QSqlQuery;


class SqlDBWriter
{
private:
    bool exec(QSqlQuery *sq, const QString &sqlFile);

    QSqlDatabase *db = nullptr;
    QSqlQuery *query = nullptr;
    bool initSuccessful = false;

protected:
    int getLastIdItems();
    int getLastIdPlayers();

    int getPlayerId(const QString &gmail);

    virtual bool checkPlayer(int id) const;
    virtual bool checkItem(int idItem, int idOwner = -1) const;

    int writeUpdatePlayerIntoDB(const QVariantMap &player) const;
    int writeUpdateItemIntoDB(const QVariantMap &item) const;
    bool getAllItemsOfPalyerFromDB(int player, QSet<int>& items);
    bool UpdateInfoOfOvners(int player, const QSet<int>);

public:
    SqlDBWriter();

    virtual bool initDb(const QString &sql = DEFAULT_DB_NAME,
                const QString &path = DEFAULT_DB_PATH);

    bool isValid() const;

    virtual ~SqlDBWriter();

};

#endif // SQLDBWRITER_H
