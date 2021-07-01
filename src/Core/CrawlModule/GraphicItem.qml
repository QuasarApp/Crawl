//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick 2.15
import QtQuick3D 1.15

Model {
    id: graphicItem

    property var model: null
    property int guiId: (model) ? model.guiId : -1;
    property bool fMapColor: model && (model.baseColorMap.length ||
                                       model.emissiveMap.length ||
                                       model.roughnessMap.length ||
                                       model.normalMap.length)

    DefaultMaterial {
        id: defaultMaterial
        diffuseColor: (model)? model.color: "#ff1111"
    }

    PrincipledMaterial {
        id:  objMaterial
        baseColorMap: Texture { source: (model)? model.baseColorMap: "" }
        emissiveMap: Texture  { source: (model)? model.emissiveMap: "" }
        roughnessMap: Texture { source: (model)? model.roughnessMap: "" }
        normalMap: Texture    { source: (model)? model.normalMap: "" }
    }

    materials: [
        (fMapColor)? objMaterial: defaultMaterial
    ]

    rotation: (model)? model.ratation: Qt.quaternion(0, 0, 0, 0)
    scale: (model)? model.size: Qt.vector3d(0, 0, 0);
    source: (model)? model.mash: "#Cube";
    position: (model) ? model.position: Qt.vector3d(0,0,0);

}
