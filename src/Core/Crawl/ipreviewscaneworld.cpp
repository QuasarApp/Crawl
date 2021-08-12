//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ipreviewscaneworld.h"
#include "previewcontrol.h"

namespace CRAWL {

IPreviewScaneWorld::IPreviewScaneWorld(const IWorld* mainWorld) {
    debug_assert(mainWorld, "The mainWorld world option should be initialized.");
    _mainWorld = mainWorld;
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

PlayableObject *IPreviewScaneWorld::initPlayer(int objectType) const {
    return _mainWorld->initPlayer(objectType);
}

bool IPreviewScaneWorld::start(const StartData& config) {
    _configuration = config;

    setPlayer(initPlayer(config.snakeType()));

    worldChanged(worldRules()->cbegin());
    setTargetFps(60);
    setRunning(true);

    return true;
}

bool IPreviewScaneWorld::stop() {
    setRunning(false);
    reset();
    return true;
}

void IPreviewScaneWorld::handleStop() {
    stop();
}

void IPreviewScaneWorld::handleRotation(double x, double y) {
    auto normal = (QQuaternion::fromEulerAngles(x, y, 0) * QVector3D{0,0,1}).normalized();

    setCameraReleativePosition(normal * 100);
    setCameraRotation(QQuaternion::rotationTo({1.0f, 0.0, 0.0}, {0,0,0}));
}

void IPreviewScaneWorld::handleStart() {
    auto playerObj = dynamic_cast<IItem*>(player());
    _configuration.setSnakePerks(playerObj->activeItems());
    emit sigPrepareIsFinished(_configuration);
    handleStop();
}

void IPreviewScaneWorld::handleSelect(int item, bool isSelected) {
    auto playerItem = dynamic_cast<IItem*>(player());

    if (isSelected) {
        playerItem->activate(item);
    } else {
        playerItem->deactivate(item);
    }
}

const StartData &IPreviewScaneWorld::configuration() const {
    return _configuration;
}

void IPreviewScaneWorld::initControl(IControl *control) {
    auto controlObject = dynamic_cast<PreviewControl*>(control);

    if (controlObject) {
        connect(controlObject, &PreviewControl::backToMenu, this, &IPreviewScaneWorld::handleStop);
        connect(controlObject, &PreviewControl::mousePositionChanged, this, &IPreviewScaneWorld::handleRotation);
        connect(controlObject, &PreviewControl::start, this, &IPreviewScaneWorld::handleStart);
        connect(controlObject, &PreviewControl::select, this, &IPreviewScaneWorld::handleSelect);

    }
}

IControl *IPreviewScaneWorld::initUserInterface() const {
    return new PreviewControl();
}

}
