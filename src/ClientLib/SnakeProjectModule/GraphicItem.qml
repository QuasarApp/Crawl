import QtQuick

Rectangle {
    id: graphicItem
    property var model: null
    property real angle: (model) ? model.angle : 0;
    property string texture: (model) ? model.texture : "";
    property int guiId: (model) ? model.guiId : -1;

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

    width: (model) ? model.w * metrix.gamePt: 0;
    height: (model) ? model.h * metrix.gamePt: 0;

    x: (model) ? model.x * metrix.gamePt - devX: 0;
    y: (model) ? model.y * metrix.gamePt - devY: 0;

    radius: (model) ? model.radius * metrix.gamePt : 0;

    transform: Rotation {
        origin.x: devX;
        origin.y: devY;
        angle: graphicItem.angle;
    }

}
