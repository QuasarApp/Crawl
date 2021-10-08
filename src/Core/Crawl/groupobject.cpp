//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "clasteritem.h"
#include "groupobject.h"

namespace CRAWL {

GroupObject::GroupObject() {

}

void GroupObject::render(unsigned int tbfMsec) {
    Q_UNUSED(tbfMsec)

    GuiObject* _this = checkminimumRequariedType<GuiObject>();

    for (ClasterItem* object: objects()) {

        if (Localpropertys *props = getLocalpropertys(object->guiId())) {

            if (!props->_rotation.isNull())
                object->setRotation(_this->rotation() * props->_rotation);

            QVector3D reCalcVectorPs = reCalcPos(props->_position,
                                              _this->rotation().toEulerAngles());

            object->setposition(_this->position() + reCalcVectorPs);
        }

    }
}

void GroupObject::installObject(ClasterItem *object,
                                const QVector3D &localPosition,
                                const QQuaternion &localRotation) {

    updatePosition(object->guiId(), localPosition);
    updateRotation(object->guiId(), localRotation);
    Claster::add(object);
}

void GroupObject::updatePosition(int id, const QVector3D &position) {
    _extrapropertys[id]._position = position;
}

void GroupObject::updateRotation(int id, const QQuaternion &roatation) {
    _extrapropertys[id]._rotation = roatation;
}

const QVector3D GroupObject::reCalcPos(const QVector3D& pos, const QVector3D &eulerAngles) const
{
    float alha = eulerAngles.z();
    float beta = eulerAngles.y();
    float gamma = eulerAngles.x();

    float x = pos.x();
    float y = pos.y();
    float z = pos.z();

    float newX = x*(qCos(alha)*qCos(beta)) +
                 y*(qCos(alha)*qSin(beta)*qSin(gamma) - qSin(alha)*qCos(gamma)) +
                 z*(qCos(alha)*qSin(beta)*qCos(gamma) + qSin(alha)*qSin(gamma));

    float newY = x*(qSin(alha)*qCos(beta)) +
                 y*(qSin(alha)*qSin(beta)*qSin(gamma) + qCos(alha)*qCos(gamma)) +
                 z*(qSin(alha)*qSin(beta)*qCos(gamma) - qCos(alha)*qSin(gamma));

    float newZ = x*(-qSin(beta)) +
                 y*(qCos(beta)*qSin(gamma)) +
                 z*(qCos(beta)*qCos(gamma));

    return QVector3D({newX, newY, newZ});
}

QQuaternion *GroupObject::getLocalrotation(int id) {
    if (_extrapropertys.contains(id)) {
        return &_extrapropertys[id]._rotation;
    }

    return nullptr;
}

QVector3D *GroupObject::getLocalPosition(int id) {
    if (_extrapropertys.contains(id)) {
        return &_extrapropertys[id]._position;
    }

    return nullptr;
}

Localpropertys *GroupObject::getLocalpropertys(int id) {
    if (_extrapropertys.contains(id)) {
        return &_extrapropertys[id];
    }

    return nullptr;
}

}
