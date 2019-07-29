import QtQuick 2.9
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    id: item1
    property alias level: level
    property var model: null
    visible: true
    z: 1

    signal playGame();


    ColumnLayout {
        id: columnLayout
        width: 642
        anchors.topMargin: 0
        transformOrigin: Item.Center
        spacing: -100
        anchors.fill: parent

        Button {
            id: play
            text: qsTr("Play game")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pixelSize: 20
            spacing: 4
            focusPolicy: Qt.StrongFocus
            display: AbstractButton.TextBesideIcon
            Layout.preferredHeight: item1.height / 5
            Layout.preferredWidth: item1.height * 0.8

            onClicked: {
                playGame();
                if (model)
                    model.newGame();
            }

        }

        Button {
            id: level
            text: qsTr("My Status")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pixelSize: 20
            Layout.preferredHeight: item1.height / 5
            Layout.preferredWidth: item1.height * 0.8
            spacing: 2

            onClicked: {
                userView._show();
            }
        }

        Button {
            id: exit
            text: qsTr("Exit")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pixelSize: 20
            Layout.preferredHeight: item1.height / 5
            Layout.preferredWidth: item1.height * 0.8

            onClicked: {
                Qt.quit();
            }
        }

    }

    RoundButton {
        id: roundButton
        x: 569
        y: 20
        height: 48
        clip: false
        anchors.right: parent.right
        anchors.rightMargin: 23
        anchors.top: parent.top
        anchors.topMargin: 20

        onClicked: {
            about._show();
        }
    }


    PagePopUp {
        id: about;
        width: parent.width / 2
        height: parent.height / 2;
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2

        source: "About.qml"
    }

    PagePopUp {
        id: userView;
        width: parent.width / 2
        height: parent.height / 2;
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2

        source: "UserView.qml"
    }

}

