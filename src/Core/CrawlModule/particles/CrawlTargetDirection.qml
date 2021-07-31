//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick
import QtQuick3D
import QtQuick3D.Particles3D

TargetDirection3D {
    property var model: null
    property string path: ""

    position: (model)? model.velosityTargetPosition : Qt.vector3d(0, 0, 0)
    normalized: (model)? model.velosityNormalized : false
    magnitude: (model)? model.velosityMagnitude : 1
    magnitudeVariation: (model)? model.velosityMagnitudeVariation : 0
    positionVariation: (model)? model.velosityTargetPositionVariation : Qt.vector3d(0, 0, 0)

}
