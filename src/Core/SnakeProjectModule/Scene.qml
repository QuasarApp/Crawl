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
    property var releativeCameraPosition: (world)? model.cameraReleativePosition: null
    property bool showMenu: false
    property bool isPause: false

    onModelChanged: {
        if (!model)
            return;

        model.scane = mainScane
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

//    MouseArea {
//        anchors.fill: parent;

//        onClicked: {
//            if (!model || showMenu) {
//                return;
//            }

//            model.buttonPress();
//        }
//    }

    Button {
        id: returnToMenu;

        text: "<<"

        anchors.left: parent.left
        anchors.leftMargin: metrix.gamePt

        anchors.top: parent.top
        anchors.topMargin: metrix.gamePt
        z: 1

        onClicked: {
            if (model)
                model.showMenu = true;
        }

        visible: !showMenu
    }

    Button {
        id: pause

        text: (isPause)?  "▶" :"||"

        anchors.left: returnToMenu.right
        anchors.leftMargin: metrix.gamePt

        anchors.top: parent.top
        anchors.topMargin: metrix.gamePt
        z: returnToMenu.z

        onClicked: {
            isPause = !isPause;
            if (model) model.setPause(isPause);
        }

        visible: !showMenu

    }

    Button {
        id: long_
        Label {
            anchors.fill: parent;

            textFormat: Text.AutoText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap

            text: qsTr("lvl long: ") + ((model)? model.long_: "0")
        }

        width: 35 * metrix.gamePt;
        height: pause.height;

        anchors.left: pause.right
        anchors.leftMargin: metrix.gamePt

        anchors.top: parent.top
        anchors.topMargin: metrix.gamePt
        z: returnToMenu.z

        visible: !showMenu

    }

    Button {
        Label {
            anchors.fill: parent;

            textFormat: Text.AutoText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap

            text: qsTr("general long: ") + ((model)? model.generalLong: "0")
        }

        width: 35 * metrix.gamePt;
        height: long_.height;

        anchors.left: long_.right
        anchors.leftMargin: metrix.gamePt

        anchors.top: parent.top
        anchors.topMargin: metrix.gamePt
        z: returnToMenu.z

        visible: !showMenu

    }
}
