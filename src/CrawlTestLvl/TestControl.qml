import QtQuick 2.15
import CrawlModule 1.0
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls 2.15

DefaultMenu {
    columns: 2
    rows: 2

    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.columnSpan: 2
        Layout.rowSpan: 2

        color: "#22000000"

        MouseArea {
            property bool track: false
            property real oldX: 0
            property real oldY: 0
            cursorShape: Qt.DragMoveCursor
            onPressed: (mouse) => {
                track = true
                oldX = mouse.x
                oldY = mouse.y

            }

            onReleased: {
                track = false
            }

            onPositionChanged: (mouse) => {
                if (!model) {
                    return;
                }

                if (!track) {
                    return;
                }

                let delta = mouse.y - oldY;
                let radianDelta = (delta / (parent.height / 2)) * 45

                model.yChanged(radianDelta)
                oldY = mouse.y;

                delta = mouse.x - oldX;
                radianDelta = (delta / (parent.width / 2)) * 45

                model.xChanged(radianDelta)
                oldX = mouse.x;
            }

            anchors.fill: parent
        }
    }


}
