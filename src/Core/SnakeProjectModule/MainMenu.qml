import QtQuick 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

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
        width: 12 * metrix.controlPtMaterial
        height: 8 * metrix.controlPtMaterial;

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
        }

        standardButtons: Dialog.Cancel | Dialog.Ok
        modal: false;
        width: 12 * metrix.controlPtMaterial
        height: 8 * metrix.controlPtMaterial;

        onAccepted: {
            if (!item1.model)
                return;

            item1.model.newGame(view.selectedLvl)
        }
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
