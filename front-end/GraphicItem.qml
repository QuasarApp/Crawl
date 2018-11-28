import QtQuick 2.9

Rectangle {
    id: graphicItem
    property var model: null
    property real angle: (model) ? model.angle : 0;
    property string texture: (model) ? model.texture : "";
    property int guiId: (model) ? model.color : -1;

    z:-1
    property double devX: width / 2
    property double devY: height / 2

    Image {
        id: name
        visible: texture.length
        source: texture

        anchors.fill: parent;
    }

    color: (model) ? model.color : "#11ff32";

    width: (model) ? model.w * mainWindow.point: 0;
    height: (model) ? model.h * mainWindow.point: 0;

    x: (model) ? model.x * mainWindow.point - devX: 0;
    y: (model) ? model.y * mainWindow.point - devY: 0;

    transform: Rotation {
        origin.x: devX;
        origin.y: devY;
        angle: graphicItem.angle;
    }

}
