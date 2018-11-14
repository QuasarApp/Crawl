import QtQuick 2.9

Item {
    id: scene;
    property var model: contr;

    property var arrayObjects: []
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
// todo: array object delete;
    function remove(id) {
        if (typeof id !== "number" || id < 0) {
            console.log("id not found");
            return;
        }

        for (var i = 0; i < arrayObjects.length; ++i) {
            if (id === arrayObjects[i].guiId) {
                arrayObjects[i].guiId = null;
            }
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
    }
}
