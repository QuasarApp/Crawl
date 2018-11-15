import QtQuick 2.9

Rectangle {
    id: graphicItem
    property var model: null
    property real angle: (model) ? model.angle : 0;
    property string texture: (model) ? model.texture : "";
    property rect rec: (model) ? model.rect : Qt.rect(0, 0, 0, 0);
    property int guiId: (model) ? model.color : -1;

    color: (model) ? model.color : "#11ff32";
    width: rec.width * mainWindow.point;
    height: rec.height * mainWindow.point;
    x: rec.x * mainWindow.point;
    y: rec.y * mainWindow.point;

    transform: Rotation {
        origin.x: rec.x / 2;
        origin.y: rec.y / 2;
        angle: graphicItem.angle;
    }

}
