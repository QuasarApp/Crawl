import QtQuick
import QtQuick3D

Model {
    id: graphicItem

    property var model: null
    property int guiId: (model) ? model.guiId : -1;

    DefaultMaterial {
        id: material_001_material
        diffuseColor: "#ffcccccc"
    }

    materials: [
        material_001_material
    ]

    rotation: (model)? model.ratation: Qt.quaternion(0, 0, 0, 0)
    scale: (model)? model.size: Qt.vector3d(0, 0, 0);
    source: (model)? model.mash: "#Cube";
    position: (model) ? model.position: Qt.vector3d(0,0,0);

}
