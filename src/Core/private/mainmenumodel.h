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
class AvailableLevelsModel;

/**
 * @brief The MainMenuModel class This is main class for controll user interface
 */
class MainMenuModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* userSettingsModel READ userSettingsModel NOTIFY userSettingsModelChanged)
    Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QObject * storeView READ storeView NOTIFY storeViewChanged)
    Q_PROPERTY(AvailableLevelsModel * selectLevelModle READ selectLevelModle NOTIFY selectLevelModleChanged)

public:
    MainMenuModel(QObject *ptr = nullptr);
    ~MainMenuModel();

    /**
     * @brief userSettingsModel This method return pointer to the setting model.
     * @return This is pointer to setting model.
     */
    QObject* userSettingsModel() const;

    /**
     * @brief getVisible This method return visible property of the main game menu.
     * @return true if the menu is visble.
     */
    bool getVisible() const;

    /**
     * @brief setVisible This method will change visible of the main menu.
     * @param newVisible This is new vlaue of the visible.
     */
    void setVisible(bool newVisible);

    /**
     * @brief storeView This method return pointer to store view model
     * @return pointer to store view model
     */
    QObject *storeView() const;

    /**
     * @brief selectLevelModle This method return pointer to the available levels model.
     * @return pointer to main available levels model.
     */
    AvailableLevelsModel *selectLevelModle() const;


signals:
    void userSettingsModelChanged(QObject* userSettingsModel);
    void visibleChanged();
    void storeViewChanged();
    void selectLevelModleChanged();

private:
    Settings *_conf = nullptr;
    QObject* _userSettingsModel = nullptr;
    bool visible = true;
    StoreViewModel *_storeView = nullptr;
    AvailableLevelsModel *_selectLevelModle = nullptr;

};

}
#endif // NETWORKPROFILEMAINMODEL_H
