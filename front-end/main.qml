import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

ApplicationWindow {
    id: mainWindow;
    visible: true;
    width: 1140;
    height: 540;
    title: qsTr("SnakeOnTheRoad");

    readonly property int pointCount: 100;

    property real point: (width < height) ? width/pointCount : height/pointCount;

    Scene {
        anchors.fill: parent;
    }



}
