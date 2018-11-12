import QtQuick 2.9
import QtQuick.Window 2.2
import Controller 1.0

Window {
    visible: true
    width: 1140
    height: 540
    title: qsTr("SnakeOnTheRoad")

    readonly property int pointCount: 100;

    property real point: (width < height) ? width/pointCount : height/pointCount;

    onPointChanged: {
        console.log(point);
    }

}
