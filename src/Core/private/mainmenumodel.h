//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef NETWORKPROFILEMAINMODEL_H
#define NETWORKPROFILEMAINMODEL_H

#include <QObject>
#include "settings.h"

namespace ViewSolutions {
class ListViewModel;
}

namespace CRAWL {

class WorldInfo;
class StoreViewModel;

/**
 * @brief The MainMenuModel class This is main class for controll user interface
 */
class MainMenuModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* userSettingsModel READ userSettingsModel NOTIFY userSettingsModelChanged)
    Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QObject * storeView READ storeView NOTIFY storeViewChanged)

public:
    MainMenuModel(QObject *ptr = nullptr);
    ~MainMenuModel();
    QObject* userSettingsModel() const;

    bool getVisible() const;
    void setVisible(bool newVisible);

    /**
     * @brief storeView This method return pointer to store view model
     * @return pointer to store view model
     */
    QObject *storeView() const;

signals:
    void userSettingsModelChanged(QObject* userSettingsModel);

    void visibleChanged();

    void storeViewChanged();

private:
    Settings *_conf = nullptr;
    QObject* _userSettingsModel = nullptr;
    bool visible = true;
    StoreViewModel *_storeView = nullptr;

};

}
#endif // NETWORKPROFILEMAINMODEL_H
