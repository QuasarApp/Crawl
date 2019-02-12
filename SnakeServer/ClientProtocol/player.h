#ifndef PLAYER_H
#define PLAYER_H
#include "clientprotocol_global.h"

#include <QDataStream>
#include <QList>

class CLIENTPROTOCOLSHARED_EXPORT Player {
private:
    QString _name = "";
    QString _post = "";
    unsigned int _maney = 0;
    unsigned int _record = 0;
    QList<int> _items;
    unsigned int _currentSnake;

public:
    Player();
    ~Player();

    QString name() const;
    void setName(const QString &name);
    QString post() const;
    void setPost(const QString &post);
    unsigned int maney() const;
    void setManey(unsigned int maney);
    unsigned int record() const;
    void setRecord(unsigned int record);
    QList<int> items() const;
    void setItems(const QList<int> &items);
    unsigned int currentSnake() const;
    void setCurrentSnake(unsigned int currentSnake);

    bool isValid() const;

    friend QDataStream &operator >>(QDataStream& stream, Player& data);
    friend QDataStream &operator <<(QDataStream& stream, const Player& data);

};

#endif // PLAYER_H
