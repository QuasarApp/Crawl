#ifndef SQLDBCASHE_H
#define SQLDBCASHE_H
#include "sqldbwriter.h"

#include <QMap>
#include <QHash>
#include <QSet>
#include <QVariantMap>
#include <player.h>
#include <clientprotocol.h>

enum class SqlDBCasheWriteMode: int {
    Default = 0x0,
    On_New_Thread = 0x1,
    Force = 0x2,
} ;

namespace ClientProtocol {
    class BaseNetworkObject;
}

class SqlDBCache : private SqlDBWriter
{
private:
    qint64 lastUpdateTime = 0;
    qint64 updateInterval = DEFAULT_UPDATE_INTERVAL;

    QMap <int, ClientProtocol::Package> items;
    QMap <int, PlayerDBData*> players;
    QHash <int, QSet<int>>  owners;

    int generateIdForItem() const;
    int generateIdForPalyer() const;

    bool checkPlayer(int id) override;
    bool checkItem(int idItem, int idOwner = -1) override;

    void globalUpdateDataBasePrivate(qint64 currentTime);
    void globalUpdateDataBase(SqlDBCasheWriteMode mode = SqlDBCasheWriteMode::Default);

    bool itemIsFreeFrom(int item) const override ;

public:
    SqlDBCache(qint64 updateInterval = DEFAULT_UPDATE_INTERVAL);
    ~SqlDBCache() override;

    bool initDb(const QString &sql = DEFAULT_DB_NAME,
                const QString &path = DEFAULT_DB_PATH) override;

    ClientProtocol::BaseNetworkObject * getItem(int id) override;
    int saveItem(const Item& item) override;
    PlayerDBData* getPlayer(int id) override;
    int savePlayer(const PlayerDBData &player) override;

    bool giveAwayItem(int player, int item);
    bool getItem(int player, int item, bool check = true);
    bool moveItem(int owner, int receiver, int item);

    bool getAllItemsOfPalyer(int player, QSet<int>& items) override;

    friend class testSankeServer;
};

#endif // SQLDBCASHE_H
