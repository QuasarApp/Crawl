//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

AbstractMenuView {

    columns: 2
    rows: 2

    Button {
        text: qsTr("Back to menu.")
        onClicked: {
            if (model) {
                model.backToMenu()
            }
        }
    }

    MouseArea {
        property bool track: false
        property real oldX: 0
        property real oldY: 0
        cursorShape: Qt.DragMoveCursor

        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.columnSpan: 2
        Layout.rowSpan: 2

        onClicked: {
            model.userTap()
        }
    }

}
