import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12

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

    DropShadow {
        anchors.fill: img
        horizontalOffset: (hold)? 20: (hovered)? 10: 5
        verticalOffset: (hold)? 20: (hovered)? 10: 5
        radius: 8.0
        samples: 17
        Behavior on horizontalOffset {

            ColorAnimation {
                duration: 200
            }
        }

        Behavior on verticalOffset {

            ColorAnimation {
                duration: 200
            }
        }


        Behavior on color {

            ColorAnimation {
                duration: 200
            }
        }
        color: (hold)? "#80000000": (hovered)? "#60000000": "#40000000"
        source: img
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
