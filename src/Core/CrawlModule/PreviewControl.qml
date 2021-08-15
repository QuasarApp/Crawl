//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick
import QtQuick.Controls.Material
import QtQuick.Controls
import QtQuick.Layouts

AbstractMenuView {
    columns: 4
    rows: 2

    MouseArea {
        cursorShape: Qt.DragMoveCursor

        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.columnSpan: 4
        Layout.rowSpan: 1

        onClicked: {
            model.userTap()
        }


        property bool track: false
        property real oldX: 0
        property real oldY: 0

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
                               let radianDeltaY = (delta / (parent.height / 2)) * 45

                               delta = mouse.x - oldX;
                               let radianDeltaX = (delta / (parent.width / 2)) * 45

                               model.mousePositionChanged(radianDeltaX, radianDeltaY)
                               oldY = mouse.y;
                               oldX = mouse.x;

                           }
    }

    Button {
        text: qsTr("Back to menu.")
        onClicked: {
            if (model) {
                model.backToMenu()
            }
        }
    }

    Button {
        text: qsTr("Start")
        onClicked: {
            if (model) {
                model.backToMenu()
            }
        }
    }
}
