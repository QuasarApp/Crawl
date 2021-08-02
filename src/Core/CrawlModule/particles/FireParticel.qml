//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick
import QtQuick3D
import QtQuick3D.Particles3D

SpriteParticle3D {

    id: particleFire
    sprite: Texture {
        source: "qrc:/CrawlCoreAssets/particles/sphere.png"
    }
    colorTable: Texture {
        source: "qrc:/CrawlCoreAssets/particles/fireColorTable.png"
    }
    maxAmount: 300
    color: "#ffffff"
    colorVariation: Qt.vector4d(0.0, 0.6, 0.8, 0.0)
    billboard: true
    blendMode: SpriteParticle3D.Screen
    fadeInDuration: 100
}
