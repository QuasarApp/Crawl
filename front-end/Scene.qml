import QtQuick 2.9

Item {
    id: scene;
    property var model: (contr)? contr: null;
    property var arrayObjects: []
    signal showMenu();
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
            var gameLvl = lvl;
            var dist = distance;

            if (isVictory ) {
                model.nextLvl();
            } else if (autoTimer.running) {
                model.newGame();
            } else {
                showMenu();
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
}
