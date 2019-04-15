#ifndef SQLDATABASE_H
#define SQLDATABASE_H
#include <QObject>
#include <QSqlDatabase>
#include <QDir>
#include <QMap>

#define DEFAULT_DB_NAME "SnakeDatabase.db"
#define DEFAULT_DB_PATH QDir::homePath() + "/SnakeServer"
#define DEFAULT_UPDATE_INTERVAL 3600000 // 1 hour

class QSqlQuery;
class QSqlDatabase;
class QSqlQuery;

class SQLDataBase : public QObject{

    Q_OBJECT
private:

    qint64 lastUpdateTime = 0;

    bool exec(QSqlQuery *sq, const QString &sqlFile);
    QSqlDatabase *db = nullptr;
    QSqlQuery *query = nullptr;
    bool initSuccessful = false;
    QMap <int, QVariantMap> items;
    QMap <int, QVariantMap> players;
    QHash <int, QSet<int>>  owners;
    QThread *dbThread = nullptr;

    int getPlayerId(const QString &id);

    bool initIdItems();
    bool initIdPlayers();
    int generateIdForItem() const;
    int generateIdForPalyer() const;

    bool checkPlayer(int id) const;
    bool checkItem(int idItem, int idOwner = -1) const;

    int writeUpdatePlayerIntoDB(const QVariantMap &player) const;
    int writeUpdateItemIntoDB(const QVariantMap &item) const;

    bool getAllItemsOfPalyerFromDB(int player, QSet<int>& items);

    void globalUpdateDataBasePrivate(qint64 currentTime);
    void globalUpdateDataBase(bool force = false);

    /**
      warning is function is wery cost
     * @brief itemIsFreeFromCache
     * @param item
     * @return
     */
    bool itemIsFreeFromCache(int item) const;

    bool UpdateInfoOfOvners(int player, const QSet<int>);

public:
    explicit SQLDataBase(QObject * ptr = nullptr);
    bool initDb(const QString &sql = DEFAULT_DB_NAME,
                const QString &path = DEFAULT_DB_PATH);
    bool isValid() const;

    bool getItem(int id, QVariantMap &res) const;
    int saveItem(QVariantMap &item);

    bool getPlayer(int id, QVariantMap &res) const;
    bool getPlayer(const QString& gmail, QVariantMap &res) const;

    int savePlayer(QVariantMap &player);

    bool giveAwayItem(int player, int item);
    bool getItem(int player, int item, bool check = true);
    bool moveItem(int owner, int receiver, int item);

    bool getAllItemsOfPalyer(int player, QSet<int>& items);
    ~SQLDataBase();

    friend class testSankeServer;
};

#endif // SQLDATABASE_H
