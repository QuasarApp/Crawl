import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


View3D {
    id: scene;

    property var model: null;
    property var arrayObjects: []
    readonly property bool showMenu: (model)? model.showMenu: false
    property bool isPause: false

    function add (cppObjId) {
        if (!model) {
            console.log("create object fail")
            return;
        }
        var objModel = model.getGameObject(cppObjId);

        if (!objModel) {
            console.log("object model not found");
            return;
        }

        var viewTemplate = objModel.viewTemplate;

        var temp = Qt.createComponent( viewTemplate + ".qml")
        if (temp.status === Component.Ready) {
            var obj = temp.createObject(mainScane) // parent - это обьект на который будет помещен соззданный элемент
            obj.model = model.getGameObject(cppObjId);
            arrayObjects.push(obj)
        } else {
            console.log("wrong viewTemplate in model. Message: " + temp.errorString());
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

    function updateBackgroundColor(lvl) {
        switch(lvl % 7) {
        case 0: background.clearColor = "#d6eaf8"; break;
        case 1: background.clearColor = "#d0ece7"; break;
        case 2: background.clearColor = "#d4efdf"; break;
        case 3: background.clearColor = "#fcf3cf"; break;
        case 4: background.clearColor = "#f6ddcc"; break;
        case 5: background.clearColor = "#f2d7d5"; break;
        case 6: background.clearColor = "#ebdef0"; break;
        case 7: background.clearColor = "#fbfcfc"; break;

        }
    }

    PerspectiveCamera {
        id: camera
        position: Qt.vector3d(0, 0, 100)
        eulerRotation.y: -45
        eulerRotation.z: -90

    }

    DirectionalLight {
    }

    environment: SceneEnvironment {
        id: background
        clearColor: window.color
        backgroundMode: SceneEnvironment.SkyBox
        //probeOrientation: Qt.vector3d(0, -90, 0)

        lightProbe: Texture {
            source: "qrc:/hdr/res/hdr/lebombo_2k.hdr"
        }
    }

    Node {
        id: mainScane
    }

    Timer {
        id: autoTimer;
        repeat: true;
        running: showMenu;
        interval: 1000
        onTriggered: {
            interval = Math.random() * 600
            scene.model.buttonPress();
        }
    }

    Connections {
        target: model;
        function onGameObjectsChanged(dif) {
            if (!dif) {
                console.log("dif not found");
                return;
            }

            var tempDifRem = [];
            tempDifRem = dif.getRemoveIds();
            var tempDifAdd = [];
            tempDifAdd = dif.getAddedIds();

            for (var i = 0; i < tempDifAdd.length; ++i) {
                add(tempDifAdd[i]);
            }

            for (i = 0; i < tempDifRem.length; ++i) {
                remove(tempDifRem[i]);
            }
        }
    }

    Component.onCompleted: {
        updateBackgroundColor(0);
        model.handleNewGame();

    }

    MouseArea {
        anchors.fill: parent;

        onClicked: {
            if (!model || showMenu) {
                return;
            }

            model.buttonPress();
        }
    }

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
