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
    property alias showMenu: privateRoot.showMenu
    renderMode: View3D.Underlay

    PerspectiveCamera {
        id: camera
        position: (privateRoot.player && privateRoot.releativeCameraPosition)?
                      Qt.vector3d(privateRoot.player.position.x + privateRoot.releativeCameraPosition.x,
                                  privateRoot.player.position.y + privateRoot.releativeCameraPosition.y,
                                  privateRoot.player.position.z + privateRoot.releativeCameraPosition.z)
                          :
                      Qt.vector3d(0,0,100)

        rotation: (privateRoot.world)? privateRoot.world.cameraRatation: Qt.quaternion(0,0,0,0)

    }

    PointLight {
        position: camera.position
        rotation: camera.rotation

        brightness: 250
    }

    environment: SceneEnvironment {
        id: background
        backgroundMode: SceneEnvironment.SkyBox
        lightProbe: Texture {
            source: (model)? model.hdr: ""
        }
    }

    Node {
        id: privateRoot

        property var arrayObjects: []
        property var world: (model)? model.world: null
        property int oldPlayerId: -1

        property var gameMenuModel: (model)? model.menu: null
        property var player: (world)? world.player: null
        property var releativeCameraPosition: (world)? world.cameraReleativePosition: null
        property var progress: (model)? model.prepareLvlProgress: null

        property var gameMenu: null
        property bool showMenu: (world)? WorldStatus.Game !== world.worldStatus : false;

        function add (cppObjId) {
            if (!model) {
                console.log("create object fail")
                return;
            }

            const objModel = model.getGameObject(cppObjId);

            if (!objModel) {
                console.log("object model not found");
                return;
            }

            var viewTemplate = objModel.viewTemplate;

            var temp = Qt.createComponent(viewTemplate)
            if (temp.status === Component.Ready) {
                var obj = temp.createObject(privateRoot)
                obj.model = model.getGameObject(cppObjId);
                arrayObjects.push(obj)
            } else {
                console.log("wrong viewTemplate in model " + temp.errorString());
            }
        }

        function remove(id) {
            if (typeof id !== "number" || id < 0) {
                console.log("id not found");
                return;
            }

            for (var i = 0; i < arrayObjects.length; ++i) {
                if (id === arrayObjects[i].guiId) {
                    arrayObjects.splice(i,1);
                }
            }
        }

        Connections {
            target: privateRoot.world;
            function onSigOBjctsListChanged(diff) {
                if (!diff) {
                    console.log("dif not found");
                    return;
                }

                let tempDifRem = [];
                tempDifRem = diff.getRemoveIds();
                let tempDifAdd = [];
                tempDifAdd = diff.getAddedIds();

                for (let i = 0; i < tempDifAdd.length; ++i) {
                    privateRoot.add(tempDifAdd[i]);
                }

                for (let j = 0; j < tempDifRem.length; ++j) {
                    privateRoot.remove(tempDifRem[j]);
                }
            }
        }

        Connections {
            target: privateRoot;

            function onPlayerChanged() {

                if (!privateRoot.player)
                    return

                if (privateRoot.oldPlayerId >= 0) {
                    privateRoot.remove(privateRoot.oldPlayerId);
                }

                privateRoot.add(privateRoot.player.guiId);
                privateRoot.oldPlayerId = privateRoot.player.guiId
            }

            function onGameMenuModelChanged() {
                if (!privateRoot.gameMenuModel) {
                    return;
                }

                const comp = Qt.createComponent(privateRoot.gameMenuModel.view);
                if (comp.status === Component.Ready) {
                    if (privateRoot.gameMenu) {
                        privateRoot.gameMenu.destroy()
                    }

                    privateRoot.gameMenu = comp.createObject(scene);
                    if (privateRoot.gameMenu === null) {
                        // Error Handling
                        console.log("Error creating object");
                    }

                    privateRoot.gameMenu.model = privateRoot.gameMenuModel;

                } else if (comp.status === Component.Error) {
                    // Error Handling
                    console.log("Error loading component: " + privateRoot.gameMenuModel.view, comp.errorString());
                }
            }

            function onShowMenuChanged() {
                if (privateRoot.gameMenu) {
                    privateRoot.gameMenu.visible = !showMenu
                }
            }
        }
    }
}
