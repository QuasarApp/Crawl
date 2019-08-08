#ifndef USERVIEW_H
#define USERVIEW_H

#include "playerclientdata.h"

#include <QObject>

class UserView : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY sourceChanged)
    Q_PROPERTY(QString gmail READ gmail  NOTIFY sourceChanged)
    Q_PROPERTY(int money READ money NOTIFY sourceChanged)
    Q_PROPERTY(int record READ record  NOTIFY sourceChanged)
    Q_PROPERTY(int avgRecord READ avgRecord NOTIFY sourceChanged)
    Q_PROPERTY(int cureentSnake READ cureentSnake NOTIFY sourceChanged)
    Q_PROPERTY(int id READ id NOTIFY sourceChanged)
    Q_PROPERTY(bool offline READ offline NOTIFY offlineChanged)

private:
    const PlayerClientData *_source = nullptr;

    bool _offline = false;

public:
    explicit UserView(QObject *parent = nullptr);

    QString name() const;
    QString gmail() const;
    int money() const;
    int record() const;
    int avgRecord() const;
    int cureentSnake() const;
    int id() const;

    const PlayerClientData *getSource() const;
    void setSource(const PlayerClientData *value);
    bool offline() const;
    void setOffline(bool offline);

signals:

    void sourceChanged();

    void offlineChanged(bool offline);

public slots:
};

#endif // USERVIEW_H
