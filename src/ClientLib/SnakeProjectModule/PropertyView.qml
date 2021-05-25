import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12

Item {
    id: properyView

    height: 1 * metrix.pt

    property string keyImage: "";
    property string keyText: "";

    property string valueImage: "";
    property string valueText: "";

    property int lineWidth : 0.5 * metrix.mm

    property bool hovered: false
    property bool hold: false

    Rectangle {
        id:background
        anchors.fill: parent
        color: "#00000000"

        Rectangle {
            height: lineWidth
            color: (hold)? Material.accent: (hovered)? Material.foreground:"#aaa"
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            Behavior on color {

                ColorAnimation {
                    duration: 100
                }
            }
        }
    }

    DropShadow {
        anchors.fill: background
        horizontalOffset: 2
        verticalOffset: 2
        radius: 8.0
        samples: 17

        color:  "#80000000";
        source: background
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
        }

        onPressed: {
            parent.hold = true;
        }
    }

    RowLayout {

        Label {
            text: keyText
            visible: keyText
            Layout.alignment: Qt.AlignLeft
            horizontalAlignment: Text.AlignLeft

        }

        ImageView {
            visible: keyImage
            drawItem: keyImage
            size: parent.height * 0.75

            Layout.alignment: Qt.AlignLeft
        }


        Label {
            text: valueText
            visible: valueText
            horizontalAlignment: Text.AlignRight

            Layout.fillWidth: true

            Layout.alignment: Qt.AlignRight

        }

        ImageView {
            drawItem: valueImage
            size: parent.height * 0.75
            visible: valueImage

            Layout.alignment: Qt.AlignRight


        }
        anchors.fill: parent
    }


}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
