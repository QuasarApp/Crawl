import QtQuick 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    id: imageView
    property int size: 50
    property double ratio: 1
    property string drawItem: ""
    property bool hovered: false
    property bool hold: false

    signal clicked();

    width: size * ratio
    height: size

    Image {
        id: img
        fillMode: Image.PreserveAspectFit
        source: drawItem
        sourceSize: Qt.size(width, height)
        smooth: true
        visible: false
        anchors.fill: parent
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            parent.hovered = true;
        }

        onExited: {
            parent.hovered = false;
        }

        onReleased: {
            parent.hold = false;
            imageView.clicked();
        }

        onPressed: {
            parent.hold = true;
        }
    }

}
