//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef WORLDVIEWDATA_H
#define WORLDVIEWDATA_H

#include <QObject>

class IWorld;

/**
 * @brief The WorldViewData class Simaple class for view world status in gui interface.
 */
class WorldViewData: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY dataChanged)
    Q_PROPERTY(QString desc READ desc NOTIFY dataChanged)
    Q_PROPERTY(int cost READ cost NOTIFY dataChanged)
    Q_PROPERTY(bool unlocked READ unlocked WRITE setUnlocked NOTIFY unlockedChanged)
    Q_PROPERTY(QString image READ image NOTIFY dataChanged)

public:
    WorldViewData(const IWorld * data);
    QString name() const;
    QString desc() const;

    int cost() const;
    bool unlocked() const;
    void setUnlocked(bool newUnlocked);

    QString image() const;

    void setWorldObject(const IWorld *newWorldObject);

private:
    bool m_unlocked;
    const IWorld* _worldObject = nullptr;

signals:
    void dataChanged();
    void unlockedChanged();
};

#endif // WORLDVIEWDATA_H
