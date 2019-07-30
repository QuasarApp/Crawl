import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12

Item {
    id: element
    SwipeView {
        id: swipeView
        anchors.bottom: parent.bottom
        anchors.top: tabBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        clip: true

        currentIndex: tabBar.currentIndex

        Item {
            id: loginPage

            ColumnLayout {
                id: columnLayout
                anchors.fill: parent

                TextField {
                    placeholderText: "Write Your Email"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                }

                TextField {
                    placeholderText: qsTr("Write Your passsword")

                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                    echoMode: TextInput.Password
                    cursorVisible: true
                    Layout.fillWidth: true


                }

                Button {
                    text: qsTr("sign in")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                }
            }
        }

        Item {
            id: rigisterPage
            ColumnLayout {

                anchors.fill: parent


                TextField {
                    placeholderText: "Write Your Email"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true

                }

                TextField {
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true

                    placeholderText: qsTr("Write Your Name")
                    echoMode: TextInput.NoEcho
                    cursorVisible: true

                }

                TextField {
                    placeholderText: qsTr("Write Your passsword")

                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    echoMode: TextInput.Password
                    cursorVisible: true
                }

                Button {
                    text: qsTr("sign Up")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                }
            }
        }
    }

    TabBar {
        id: tabBar
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        TabButton {
            id: login
            text: qsTr("Sign in")
            checkable: false
        }

        TabButton {
            id: register
            text: qsTr("Sign Up")
        }
    }



}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_height:100;anchors_width:100;anchors_x:228;anchors_y:63}
D{i:1;anchors_height:200;anchors_width:200;anchors_x:205;anchors_y:53}D{i:11;anchors_width:240;anchors_x:226;anchors_y:21}
}
 ##^##*/
