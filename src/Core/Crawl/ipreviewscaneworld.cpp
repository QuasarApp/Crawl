//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "ipreviewscaneworld.h"
#include "previewcontrol.h"

namespace CRAWL {

IPreviewScaneWorld::IPreviewScaneWorld() {

    setCameraReleativePosition({0, 100, 100});
    setCameraRotation(QQuaternion::fromEulerAngles(-40,0,0));
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

    if (!setPlayer(config.snakeType())) {
        return false;
    };

    worldChanged(worldRules()->cbegin());
    setTargetFps(60);
    setVisible(true);
    startRenderLoop();

    return true;
}

bool IPreviewScaneWorld::stop() {
    stopRenderLoopWithClearItems();
    setVisible(false);

    return true;
}

void IPreviewScaneWorld::handleRotation(double x, double y) {
    auto rotation = cameraRotation() * QQuaternion::fromEulerAngles(x, y, 0);
    auto normal = (rotation * QVector3D{0,0,1}).normalized();

    setCameraReleativePosition(normal * 100);
    setCameraRotation(rotation);
}

void IPreviewScaneWorld::handleStart() {
    auto playerObj = dynamic_cast<IItem*>(player());
    _configuration.setSnakePerks(playerObj->activeItems());
    emit sigPrepareIsFinished(_configuration);
    stop();
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
        connect(controlObject, &PreviewControl::mousePositionChanged, this, &IPreviewScaneWorld::handleRotation);
        connect(controlObject, &PreviewControl::start, this, &IPreviewScaneWorld::handleStart);
        connect(controlObject, &PreviewControl::select, this, &IPreviewScaneWorld::handleSelect);

    }
}

IControl *IPreviewScaneWorld::initUserInterface() const {
    return new PreviewControl();
}

}
