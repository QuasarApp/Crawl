import QtQuick 2.9
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    id: item1
    visible: true


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
            font.pixelSize: 20
            spacing: 4
            focusPolicy: Qt.StrongFocus
            display: AbstractButton.TextBesideIcon
            Layout.preferredHeight: 75
            Layout.preferredWidth: 500
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                contr.newGame();
            }

        }

        Button {
            id: level
            text: qsTr("Select level")
            font.pixelSize: 20
            Layout.preferredWidth: 500
            Layout.preferredHeight: 75
            spacing: 2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            id: exit
            text: qsTr("Exit")
            font.pixelSize: 20
            Layout.preferredHeight: 75
            Layout.preferredWidth: 500
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                Qt.quit();
            }
        }

    }

    RoundButton {
        id: roundButton
        x: 569
        y: 20
        height: 20
        anchors.right: parent.right
        anchors.rightMargin: 23
        anchors.top: parent.top
        anchors.topMargin: 20
    }

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:4;anchors_height:100;anchors_width:100;anchors_x:284;anchors_y:167}
}
 ##^##*/
