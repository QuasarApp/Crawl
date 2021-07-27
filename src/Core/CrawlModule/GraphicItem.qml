//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick
import QtQuick3D

Model {
    id: graphicItem

    property var model: null
    property int guiId: (model) ? model.guiId : -1;
    property bool fMapColor: model && (model.baseColorMap.length ||
                                       model.emissiveMap.length ||
                                       model.roughnessMap.length ||
                                       model.normalMap.length)
    property int tilies: 1

    DefaultMaterial {
        id: defaultMaterial
        diffuseColor: (model)? model.color: "#ff1111"
    }

    PrincipledMaterial {
        id:  objMaterial
        roughness : 1
        baseColorMap: Texture {
            source: (model)? model.baseColorMap: ""
            tilingModeHorizontal: (tilies > 1)? Texture.Repeat : Texture.ClampToEdge
            tilingModeVertical: (tilies > 1)? Texture.Repeat : Texture.ClampToEdge
            scaleU: tilies
            scaleV: tilies

        }

        emissiveMap: Texture  {
            source: (model)? model.emissiveMap: ""
            tilingModeHorizontal: (tilies > 1)? Texture.Repeat : Texture.ClampToEdge
            tilingModeVertical: (tilies > 1)? Texture.Repeat : Texture.ClampToEdge
            scaleU: tilies
            scaleV: tilies
        }

        roughnessMap: Texture {
            source: (model)? model.roughnessMap: ""
            tilingModeHorizontal: (tilies > 1)? Texture.Repeat : Texture.ClampToEdge
            tilingModeVertical: (tilies > 1)? Texture.Repeat : Texture.ClampToEdge
            scaleU: tilies
            scaleV: tilies
        }

        normalMap: Texture    {
            source: (model)? model.normalMap: ""
            tilingModeHorizontal: (tilies > 1)? Texture.Repeat : Texture.ClampToEdge
            tilingModeVertical: (tilies > 1)? Texture.Repeat : Texture.ClampToEdge
            scaleU: tilies
            scaleV: tilies
        }
    }

    materials: [
        (fMapColor)? objMaterial: defaultMaterial
    ]

    rotation: (model)? model.ratation: Qt.quaternion(0, 0, 0, 0)
    scale: (model)? model.size: Qt.vector3d(0, 0, 0);
    source: (model)? model.mash: "#Cube";
    position: (model) ? model.position: Qt.vector3d(0,0,0);

    visible: (model)? model.visible: false

}
