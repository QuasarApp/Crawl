import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


View3D {
    id: scene;

    property var model: null;
    property var player: (model)? model.player: null
    property var world: (model)? model.world: null
    property var gameMenuModel: (model)? model.menu: null
    property var releativeCameraPosition: (world)? model.cameraReleativePosition: null
    property bool showMenu: false
    property bool isPause: false
    property var gameMenu: null

    onModelChanged: {
        if (!model)
            return;

        model.scane = mainScane
    }

    onGameMenuModelChanged: {
        if (!gameMenuModel) {
            return;
        }

        const comp = Qt.createComponent(gameMenuModel.view);
        if (comp.status === Component.Ready) {
            if (gameMenu)
                gameMenu.destroy()

            gameMenu = comp.createObject(scene);
            if (gameMenu === null) {
                // Error Handling
                console.log("Error creating object");
            }

            gameMenu.model = gameMenuModel;

        } else if (component.status === Component.Error) {
            // Error Handling
            console.log("Error loading component:", component.errorString());
        }
    }

    PerspectiveCamera {
        id: camera
        position: (player)? Qt.vector3d(player.position.x + releativeCameraPosition.x,
                              player.position.y + releativeCameraPosition.y,
                              player.position.z + releativeCameraPosition.z)
                          :
                            Qt.vector3d(0,0,0)

        eulerRotation.z: -90

    }

    DirectionalLight {
    }

    Node {
        id: mainScane
    }

    environment: SceneEnvironment {
        id: background
        backgroundMode: SceneEnvironment.SkyBox

        lightProbe: Texture {
            source: (model)? model.hdr: ""
        }
    }
}
