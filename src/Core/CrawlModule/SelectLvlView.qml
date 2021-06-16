//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick 2.15
import ViewSolutionsModule 1.0
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    id: root

    property alias model: list.model
    property string selectedLvl: ""

    signal start(var lvlName)

    ListView {
        id: list
        Layout.fillHeight: true
        Layout.fillWidth: true
        orientation: ListView.Horizontal
        clip: true

        delegate: ImageView {
            property var data : modelData
            hoverColor: "#90f6ff"
            selectedColor: "#90f6ff"

            source: data.image
            text: data.name

            width: list.height * 1.5
            height: list.height * 0.9
            selected: selectedLvl === data.name

            onClicked:  {
                selectedLvl = text
            }
        }
    }

    Button {

        Layout.alignment: Qt.AlignRight

        text: qsTr("Start")
        enabled: selectedLvl.length

        onClicked: {
            root.start(selectedLvl)
        }

    }
}


