//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "availablelevelsmodel.h"
#include "user.h"
#include <Crawl/iitem.h>

namespace CRAWL {

AvailableLevelsModel::AvailableLevelsModel() {

}

int AvailableLevelsModel::getCurrentLevel() const {
    return currentLevel;
}

void AvailableLevelsModel::setCurrentLevel(int newCurrentLevel) {
    if (currentLevel == newCurrentLevel)
        return;
    currentLevel = newCurrentLevel;
    emit currentLevelChanged();
}

void AvailableLevelsModel::select(int levelId) {
    if (getUser()->isUnlocked(levelId)) {
        setCurrentLevel(levelId);
        emit sigUserSelectLevel(levelId);
    }
}

}
