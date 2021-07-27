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
