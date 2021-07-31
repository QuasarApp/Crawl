//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick
import QtQuick3D
import QtQuick3D.Particles3D

VectorDirection3D {
    property var model: null
    property string path: ""

    direction: (model)? model.velosityDirection : Qt.vector3d(0, 0, 0)
    directionVariation: (model)? model.velosityDirectionValatility : Qt.vector3d(0, 0, 0)
}
