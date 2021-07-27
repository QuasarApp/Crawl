//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick
import QtQuick3D

Node {
    id: graphicItem

    property var model: null
    property int guiId: (model) ? model.guiId : -1;

    PointLight {
        id : sun

        brightness: (model)? model.lightForce * model.visible: 100
        color: (model)? model.color: "#ffffff"
        castsShadow: (model)? model.castsShadow: 0
        shadowFactor: (model)? model.shadowFactor: 0
        shadowFilter: (model)? model.shadowFilter: 0
        shadowMapFar: (model)? model.shadowMapFar: 0
        shadowBias: (model)? model.shadowBias: 0
        shadowMapQuality: Light.ShadowMapQualityHigh

        Behavior on brightness {
            NumberAnimation {
                duration: 5000

            }
        }
    }

    rotation: (model)? model.ratation: Qt.quaternion(0, 0, 0, 0)
    scale: (model)? model.size: Qt.vector3d(0, 0, 0);
    position: (model) ? model.position: Qt.vector3d(0,0,0);
    visible: sun.brightness

}
