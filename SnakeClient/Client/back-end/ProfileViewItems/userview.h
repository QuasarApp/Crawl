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

private:
    const PlayerClientData *_source = nullptr;

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

signals:

    void sourceChanged();

public slots:
};

#endif // USERVIEW_H
