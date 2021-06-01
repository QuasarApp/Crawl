import QtQuick

AbstractItem {
    id: graphicItem
    property real angle: (model) ? model.angle : 0;
    property string texture: (model) ? model.texture : "";

    property double devX: width / 2
    property double devY: height / 2

    property alias color: privateRoot.color
    property alias radius: privateRoot.radius

    Rectangle {
        id: privateRoot
        Image {
            id: name
            visible: texture.length
            source: texture

            anchors.fill: parent;
        }

        color: (model) ? model.color : "#11ff32";

        radius: (model) ? model.radius * metrix.gamePt : 0;
        anchors.fill: parent

    }

    width: (model) ? model.w * metrix.gamePt: 0;
    height: (model) ? model.h * metrix.gamePt: 0;

    x: (model) ? model.x * metrix.gamePt - devX: 0;
    y: (model) ? model.y * metrix.gamePt - devY: 0;
    z:-1

    transform: Rotation {
        origin.x: devX;
        origin.y: devY;
        angle: graphicItem.angle;
    }

}

