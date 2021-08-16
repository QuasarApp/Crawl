import QtQuick
import QtQuick3D
import QtQuick.Controls.Material
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick3D.Particles3D


View3D {
    id: scene;

    property var worldModel: null;
    renderMode: View3D.Offscreen

    visible: worldModel && worldModel.visible

    Label {
        text: scane.renderStats.fps
        x: 200
    }

    PerspectiveCamera {
        id: camera
        position: (privateRoot.player && privateRoot.releativeCameraPosition)?
                      Qt.vector3d(privateRoot.player.position.x + privateRoot.releativeCameraPosition.x,
                                  privateRoot.player.position.y + privateRoot.releativeCameraPosition.y,
                                  privateRoot.player.position.z + privateRoot.releativeCameraPosition.z)
                          :
                      Qt.vector3d(0,0,100)

        rotation: (privateRoot.world)? privateRoot.world.cameraRotation: Qt.quaternion(0,0,0,0)

    }

    SceneEnvironment {
        id: defautlBackground
        backgroundMode: SceneEnvironment.Color
        clearColor: "#777777"
    }

    environment: /*(privateRoot.world)? background:*/ defautlBackground

    ParticleSystem3D {
        id: privateRoot
        property var arrayObjects: []

        property var gameMenuModel: (worldModel)? worldModel.menu: null
        property var player: (worldModel)? worldModel.player: null
        property var releativeCameraPosition: (worldModel)? worldModel.cameraReleativePosition: null

        property var gameMenu: null

        function add (cppObjId) {
            if (!worldModel) {
                console.log("create object fail")
                return;
            }

            const objModel = worldModel.getItem(cppObjId);

            if (!objModel) {
                console.log("model of the crawl object is not found");
                return;
            }

            var viewTemplate = objModel.viewTemplate;

            var temp = Qt.createComponent(viewTemplate)
            if (temp.status === Component.Ready) {
                var obj = temp.createObject(privateRoot)
                obj.model = objModel;
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
            target: worldModel;
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
        }
    }
}
