//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick 2.15
import QtQuick3D 1.15

Node {
    id: graphicItem

    property var model: null
    property int guiId: (model) ? model.guiId : -1;

    SpotLight {
        id : sun

        position: Qt.vector3d(0, 0, 100);
        brightness: (model)? model.lightForce: 100
        color: (model)? model.color: "#ffffff"
        castsShadow: (model)? model.castsShadow: 0
        shadowFactor: (model)? model.shadowFactor: 0
        shadowFilter: (model)? model.shadowFilter: 0
        shadowMapFar: (model)? model.shadowMapFar: 0
        shadowBias: (model)? model.shadowBias: 0
        eulerRotation.z: -90

        coneAngle: 300
        innerConeAngle: 0

    }


//    PointLight {
//        id: moon

//        position: Qt.vector3d(0, 0, -10000);
//        brightness: (model)? model.moonLightForce: 100
//        color: (model)? model.moonColor: "#ffffff"
//        castsShadow: (model)? model.castsShadow: 0
//        shadowFactor: (model)? model.shadowFactor: 0
//        shadowFilter: (model)? model.shadowFilter: 0
//        shadowMapFar: (model)? model.shadowMapFar: 0
//        shadowBias: (model)? model.shadowBias: 0
//        eulerRotation: Qt.vector3d(90,0,0)

//    }

    rotation: (model)? model.ratation: Qt.quaternion(0, 0, 0, 0)
    scale: (model)? model.size: Qt.vector3d(0, 0, 0);
    position: (model) ? model.position: Qt.vector3d(0,0,0);

}
