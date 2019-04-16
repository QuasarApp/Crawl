#ifndef SQLDBCASHE_H
#define SQLDBCASHE_H
#include "sqldbwriter.h"

#include <QMap>
#include <QHash>
#include <QSet>
#include <QVariantMap>

class SqlDBCashe : private SqlDBWriter
{
private:
    qint64 lastUpdateTime = 0;

    QMap <int, QVariantMap> items;
    QMap <int, QVariantMap> players;
    QHash <int, QSet<int>>  owners;

    int generateIdForItem() const;
    int generateIdForPalyer() const;

    bool checkPlayer(int id) const;
    bool checkItem(int idItem, int idOwner = -1) const;

    void globalUpdateDataBasePrivate(qint64 currentTime);
    void globalUpdateDataBase(bool force = false);

    bool itemIsFreeFromCache(int item) const;

public:
    SqlDBCashe();

    bool getItem(int id, QVariantMap &res) const;
    int saveItem(QVariantMap &item);

    bool getPlayer(int id, QVariantMap &res) const;
    bool getPlayer(const QString& gmail, QVariantMap &res) const;

    int savePlayer(QVariantMap &player);

    bool giveAwayItem(int player, int item);
    bool getItem(int player, int item, bool check = true);
    bool moveItem(int owner, int receiver, int item);

    bool getAllItemsOfPalyer(int player, QSet<int>& items);
};

#endif // SQLDBCASHE_H
