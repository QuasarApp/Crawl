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

    virtual bool checkPlayer(int id);
    virtual bool checkItem(int idItem, int idOwner = -1);

    virtual int savePlayer(QVariantMap &player);
    virtual int saveItem(QVariantMap &item);
    virtual bool saveOvners(int player, const QSet<int>);

    virtual bool getAllItemsOfPalyer(int player, QSet<int>& items);

    virtual bool getPlayer(int id, QVariantMap &res);
    virtual bool getItem(int id, QVariantMap &res);

    virtual bool itemIsFreeFrom(int item) const;

public:
    SqlDBWriter();

    virtual bool initDb(const QString &sql = DEFAULT_DB_NAME,
                const QString &path = DEFAULT_DB_PATH);

    virtual bool isValid() const;

    virtual ~SqlDBWriter();

    friend class testSankeServer;

};

#endif // SQLDBWRITER_H
