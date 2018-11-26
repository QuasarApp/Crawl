import QtQuick 2.11
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    id: scene;
    z: -2
    property var model: (contr)? contr: null;
    property var arrayObjects: []
    property bool showMenu: false
    function add (cppObjId) {
        if (!model) {
            console.log("create object fail")
            return;
        }

        var temp = Qt.createComponent("GraphicItem.qml")
        if (temp.status === Component.Ready) {
            var obj = temp.createObject(parent) // parent - это обьект на который будет помещен соззданный элемент
            obj.model = model.getGameObject(cppObjId);
            if (!obj.model) {
                console.log("object model not found");
                return;
            }
            arrayObjects.push(obj)
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

    function setAuto (auto) {
        if (auto && model) {
            model.newGame();

        }
        showMenu = (auto && model)
        autoTimer.running = auto && model;
    }

    Timer {
        id :autoTimer;
        repeat: true;
        running: false;
        interval: 1000
        onTriggered: {
            interval = Math.random() * 600
            scene.model.buttonPress();
        }
    }

    Connections {
        target: model;
        onGameObjectsChanged: {
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

        onFinished: {
            var isVictory = victory;
            var gameLvl = lvl + 1;
            var dist = distance;

            if (isVictory ) {

                if (!autoTimer.running)
                    notification.show(qsTr(" Next Lvl!!!"),
                                  qsTr(" You anblock next lvl (" + gameLvl + ")" ),
                                  "qrc:/texture/up");

                model.nextLvl();
            } else if (autoTimer.running) {
                model.newGame();
            } else {
                showMenu = true;
            }
        }
    }

    MouseArea {
        anchors.fill: parent;

        onClicked: {
            if (!model) {
                console.log("model not found");
                return;
            }

            model.buttonPress();
        }
    }

    NotificationForm {
        z: -1
        id: notification;
        margin: mainWindow.point;

        x: parent.width - width - margin;
        y: margin;

        width: 40 * mainWindow.point;
        height: width * 0.5

    }

    Button {
        id: returnToMenu;

        text: "<<"

        anchors.left: parent.left
        anchors.leftMargin: point

        anchors.top: parent.top
        anchors.topMargin: point

        visible: !showMenu
    }

    Button {
        id: pause

        text: "||"

        anchors.left: returnToMenu.right
        anchors.leftMargin: point

        anchors.top: parent.top
        anchors.topMargin: point

        visible: !showMenu

    }

    Button {
        Label {
            anchors.fill: parent;

            textFormat: Text.AutoText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap

            text: qsTr("long: ") + (model)? model.long_: "0"
        }

        width: 15 * point;
        height: pause.height;

        anchors.left: pause.right
        anchors.leftMargin: point

        anchors.top: parent.top
        anchors.topMargin: point

        visible: !showMenu

    }
}
