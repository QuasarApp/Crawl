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

Item {
    id: settingsView

    property var model: null

    function save() {
        if (!model) {
            return;
        }

        model.setPort(port.value);
        model.setHost(host.text);
        model.setTheme(themeBox.currentIndex);

    }

    function reset() {
        if (!model) {
            return;
        }

        model.toDefault();
    }

    function update() {
        if (!model) {
            return;
        }
        model.forceUpdate();
    }

    GridLayout {

        id: columnLayout
        rows: 4
        columns: 2
        anchors.fill: parent

        Label {
            text: qsTr("Use Them")
            Layout.fillWidth: true
        }

        ComboBox {
            id: themeBox;
            Layout.fillWidth: true
            focusPolicy: Qt.NoFocus

            model: [qsTr("Light"), qsTr("Dark")];
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            currentIndex: (settingsView.model)? settingsView.model.theme: 0

            onCurrentIndexChanged:  {
                if (((settingsView.model)? settingsView.model.theme: 0)
                        !== currentIndex) {
                    themeWarning.visible = true;
                }
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

        }

        Label {
            id: themeWarning
            text: qsTr("In order for the new theme to take effect, you need to reload the game.");

            color: "#FF0000"

            wrapMode: Label.WordWrap

            Layout.maximumWidth: themeBox.width

            visible: false;
        }
    }

}
