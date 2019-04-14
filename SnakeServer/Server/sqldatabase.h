#ifndef SQLDATABASE_H
#define SQLDATABASE_H
#include <QObject>
#include <QSqlDatabase>
#include <QDir>
#include <QMap>

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
    bool initSuccessful = false;
    QMap <int, void*> items;
    QMap <int, void*> players;

    bool ifExistItem(int id);
    bool existPlayer(int id);
    int getPlayerId(const QString &id);

    bool initIdItems();
    bool initIdPlayers();
    int generateIdForItem();
    int generateIdForPalyer();

public:
    SQLDataBase(QObject * ptr = nullptr);
    bool initDb(const QString &sql = DEFAULT_DB_NAME,
                const QString &path = DEFAULT_DB_PATH);
    bool isValid() const;

    bool getItem(int id, QVariantMap &res) const;
    int saveItem(const QVariantMap &item);

    bool getPlayer(int id, QVariantMap &res) const;
    bool getPlayer(const QString& gmail, QVariantMap &res) const;

    int savePlayer(const QVariantMap &player);

    bool giveAwayItem(int player, int item);
    bool getItem(int player, int item);

    friend class testSankeServer;
};

#endif // SQLDATABASE_H
