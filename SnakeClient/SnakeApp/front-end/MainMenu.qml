import QtQuick 2.9
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    id: item1
    property var model: null
    readonly property int  onlineStatus: (model)? model.onlineStatus: false

    visible: true
    z: 1

    signal playGame();

    onOnlineStatusChanged: {
        if (onlineStatus !== 4) {
            loginPopUp._show();
        }
    }

    UserView {
        id: userView
        anchors.verticalCenter: parent.verticalCenter

        anchors.left: parent.left
        anchors.leftMargin: 0


        model: (item1.model)? item1.model.userViewModel: null
    }

    GridLayout {
        id: columnLayout
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: userView.right
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
                playGame();
                if (model)
                    model.newGame();
            }

        }

        MainMenuButton {
            id: store
            text: qsTr("Store")

        }

        MainMenuButton {
            id: invitar
            text: qsTr("My Items")
        }

        MainMenuButton {
            id: freands
            text: qsTr("My friends")

        }

        MainMenuButton {
            id: settings
            text: qsTr("My Settings")

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
        id: about;
        width: parent.width / 2
        height: parent.height / 2;

        source: About {}
    }



    PagePopUp {
        id: loginPopUp
        source: LoginView {
            id: loginView
            loginStatus: onlineStatus
        }

        visible: true;
        modal: true;
        autoClose: false
        clickClose: false
        width: 10 * metrix.controlPtMaterial
        height: ((loginView.currentView)? 12 : 7) * metrix.controlPtMaterial;
    }


}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
