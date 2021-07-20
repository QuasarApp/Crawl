import QtQuick
import QtQuick3D
import QtQuick.Controls.Material
import QtQuick.Controls
import QtQuick.Layouts

// https://doc.qt.io/qt-5/qqmlengine.html#qmlRegisterUncreatableMetaObject
import engine.worldstatus

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

    environment: SceneEnvironment {
        id: background
        backgroundMode: SceneEnvironment.SkyBox
        lightProbe: Texture {
            source: (privateRoot.world)? privateRoot.world.hdr: ""
        }
    }

    Node {
        id: privateRoot

        property var arrayObjects: []
        property var world: (model)? model.world: null

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
                    arrayObjects[i].destroy();
                    arrayObjects.splice(i,1);

                }
            }
        }

        Connections {
            target: privateRoot.world;
            function onSigOBjctsListChanged(diff) {
                if (!diff) {
                    console.log("diff not found");
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
