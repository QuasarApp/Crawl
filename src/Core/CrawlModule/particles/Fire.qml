//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick
import QtQuick3D
import QtQuick3D.Particles3D

ParticleEffect {
    PointLight {
        position: parent.position
        brightness: 100 * (model)? model.fireStrength: 0;
        color: (model)? model.color: "#ffffff";
    }
}
