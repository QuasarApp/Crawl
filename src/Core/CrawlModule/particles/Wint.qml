//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick
import QtQuick3D
import QtQuick3D.Particles3D

Gravity3D {

    property var model: null
    property int guiId: (model) ? model.guiId : -1;

    enabled: (model)? model.enabled: false

    magnitude: (model)? model.magnitude: 0

    direction: (model)? model.direction: Qt.vector3d(0, 0, 0)

    Behavior on magnitude {
        NumberAnimation {
            duration: 5000
            easing.type: Easing.InQuad

        }
    }

    Behavior on direction {
        Vector3dAnimation {
            duration: 5000
            easing.type: Easing.InQuad
        }
    }

}

