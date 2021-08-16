//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "iitem.h"
#include "ilevel.h"
#include "ipreviewscaneworld.h"

namespace CRAWL {

ILevel::~ILevel() {
    delete _world;
    delete _previewScane;
}

IWorld *ILevel::world() {
    return _world;
}

IPreviewScaneWorld *ILevel::previewScane() {
    return _previewScane;
}

void ILevel::reset() {
    _world->reset();
    _previewScane->reset();
}

void ILevel::setWorld(IWorld *newWorld) {
    _world = newWorld;
}

void ILevel::setPreviewScane(IPreviewScaneWorld *newPreviewScane) {
    _previewScane = newPreviewScane;
}

}
