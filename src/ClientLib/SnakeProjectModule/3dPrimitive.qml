import QtQuick
import QtQuick3D

Node {
    id: rootNode

    property var model: null

    Model {
        id: suzanne
        rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
        scale.x: 100
        scale.y: 100
        scale.z: 100
        source: "meshes/suzanne.mesh"

        DefaultMaterial {
            id: material_001_material
            diffuseColor: "#ffcccccc"
        }
        materials: [
            material_001_material
        ]
    }
}
