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

Item {
    id: item1
    property var model: null

    visible: true
    z: 1

    GridLayout {
        id: columnLayout
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.topMargin: 0

        columns: 3
        rows: 2


        transformOrigin: Item.Center


        MainMenuButton {
            id: play
            text: qsTr("Play game")

            onClicked: {
                selectLvl.open()
            }
        }

        MainMenuButton {
            id: settings
            text: qsTr("My Settings")

            onClicked: {
                settingsPopUp.open();

            }
        }

        MainMenuButton {
            id: exit
            text: qsTr("Exit")

            onClicked: {
                Qt.quit();
            }
        }

    }

    PagePopUp {
        id: settingsPopUp
        source: SettingsView {
            id: settingsView
            model: item1.model ? item1.model.userSettingsModel: null
        }

        standardButtons:  Dialog.Save | Dialog.Cancel | Dialog.RestoreDefaults
        modal: false;
        width: parent.width * 0.8
        height: parent.height * 0.8;

        onAccepted: {
            settingsView.save();
        }

        onReset: {
            settingsView.reset();
        }

        onOpened: {
            settingsView.update();
        }

    }

    PagePopUp {
        id: selectLvl
        source: SelectLvlView {
            id: view
            model: item1.model ? item1.model.availableLvlsModel: null

            onStart: {
                if (!item1.model)
                    return;

                item1.model.newGame(view.selectedLvl)

                selectLvl.close();
            }
        }

        modal: false;
        width: parent.width * 0.8
        height: parent.height * 0.8;

    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
