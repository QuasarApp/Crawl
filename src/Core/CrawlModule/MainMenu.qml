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
    id: root
    property var model: null

    visible: Boolean(model && model.visible)
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
            text: qsTr("Select level")

            onClicked: {
                selectLvl.open()
            }
        }

        MainMenuButton {
            id: store
            text: qsTr("Store")

            onClicked: {
                storePopUp.open()
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
            model: root.model ? root.model.userSettingsModel: null
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
        id: storePopUp
        source: StoreView {
            id: view
            model: root.model ? root.model.storeView: null

        }

        modal: false;
        width: parent.width * 0.8
        height: parent.height * 0.8;

    }

    PagePopUp {
        id: selectLvl
        source: SelectLevelView {
            id: selectLvlView
            model: root.model ? root.model.availableLvlsModel: null

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
