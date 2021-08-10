//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ipreviewscaneworld.h"
namespace CRAWL {

IPreviewScaneWorld::IPreviewScaneWorld() {

}

QString IPreviewScaneWorld::itemTextId() const {
    return "preview";
}

QString IPreviewScaneWorld::itemName() const {
    return itemTextId();
}

QString IPreviewScaneWorld::description() const {
    return "";
}

QString IPreviewScaneWorld::image() const {
    return "";
}

int IPreviewScaneWorld::cost() const {
    return 0;
}

int IPreviewScaneWorld::requiredTier() const {
    return 0;
}

bool IPreviewScaneWorld::start(const StartData& config) {
    _configuration = config;
}

bool IPreviewScaneWorld::stop() {

}

}
