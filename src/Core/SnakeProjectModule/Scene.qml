import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

// https://doc.qt.io/qt-5/qqmlengine.html#qmlRegisterUncreatableMetaObject
import engine.worldstatus 1.0

View3D {
    id: scene;

    property var model: null;
    property var player: (model)? model.player: null
    property var world: (model)? model.world: null
    property var gameMenuModel: (model)? model.menu: null
    property var releativeCameraPosition: (world)? world.cameraReleativePosition: null
    property var progress: (model)? model.prepareLvlProgress: null

    property var gameMenu: null
    property bool showMenu: (world)? WorldStatus.Game !== world.worldStatus : false;

    onModelChanged: {
        if (!model)
            return;

        model.scane = mainScane
    }

    onReleativeCameraPositionChanged: {
        console.log(releativeCameraPosition)
    }

    onGameMenuModelChanged: {
        if (!gameMenuModel) {
            return;
        }

        const comp = Qt.createComponent(gameMenuModel.view);
        if (comp.status === Component.Ready) {
            if (gameMenu) {
                gameMenu.destroy()
            }

            gameMenu = comp.createObject(scene);
            if (gameMenu === null) {
                // Error Handling
                console.log("Error creating object");
            }

            gameMenu.model = gameMenuModel;

        } else if (comp.status === Component.Error) {
            // Error Handling
            console.log("Error loading component: " + gameMenuModel.view, comp.errorString());
        }
    }

    onShowMenuChanged: {
        if (gameMenu) {
            gameMenu.visible = !showMenu
        }
    }

    PerspectiveCamera {
        id: camera
        position: (player)? Qt.vector3d(player.position.x + releativeCameraPosition.x,
                              player.position.y + releativeCameraPosition.y,
                              player.position.z + releativeCameraPosition.z)
                          :
                            Qt.vector3d(0,0,0)

        rotation: (world)? world.cameraRatation: Qt.quaternion(0,0,0,0)

    }

    DirectionalLight {
        position: Qt.vector3d(0,0,100)
        eulerRotation.z: 90

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
