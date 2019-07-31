import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12

Item {
    id: element

    // -1 general state (Without Data)
    // -2 wait for ansever
    property int loginStatus : -1
    readonly property var resultLoginEnum: [
        qsTr("Success"), // 0
        qsTr("Authorization fail"), // 1
        qsTr("Client is offline "), // 2
    ]

    readonly property int currentView: tabBar.currentIndex
    readonly property var resultEnum: [
        qsTr("Success"), // 0
        qsTr("Password must be at least 8 characters"), // 1
        qsTr("Name must be at least 1 characters"), // 2
        qsTr("Passwords must match"), // 3

        qsTr("The letter must match the pattern 'X@xxxx.xxx'") // 4

    ]

    signal sigNewUser(var gmail, var userName, var password);
    signal sigLogin(var gmail, var password);


    function _checkLogin() {
        const pass = loginPass.text;
        const email = loginEmail.text;

        if (pass.length < 8) {
            return 1;
        }

        if (email.search(/[a-z\-A-Z0-9_]+@[a-z\-A-Z0-9_]+\.[a-z\-A-Z0-9_]+/) < 0) {
            return 4;
        }

        return 0;

    }

    function _checkRegister () {
        const pass = registerPassword.text;
        const pass2 = registerPassword2.text;

        const email = registerEmail.text;
        const login = registerName.text;

        if (pass.length < 8) {
            return 1;
        }

        if (login.length < 1) {
            return 3;
        }

        if (pass !== pass2) {
            return 3;
        }

        if (email.search(/[a-z\-A-Z0-9_]+@[a-z\-A-Z0-9_]+\.[a-z\-A-Z0-9_]+/) < 0) {
            return 4;
        }

        return 0;
    }

    function checkData(isregisterForm) {
        if (isregisterForm) {
            return _checkRegister();
        }

        return _checkLogin();
    }

    function waitforAnsver() {
        loginStatus = -2;
    }

    SwipeView {
        id: swipeView
        anchors.bottom: bottons.top
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

                Label {
                    text: qsTr("Email")
                }
                TextField {
                    id: loginEmail
                    placeholderText: "Enter Your Email"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                }

                Label {
                    text: qsTr("Passsword")
                }
                TextField {
                    id: loginPass
                    placeholderText: qsTr("Enter Your passsword")

                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                    echoMode: TextInput.Password
                    cursorVisible: true
                    Layout.fillWidth: true

                }
            }
        }

        Item {
            id: rigisterPage
            ColumnLayout {

                anchors.fill: parent


                Label {
                    text: qsTr("Email")
                }
                TextField {
                    id: registerEmail;
                    placeholderText: qsTr("Enter Your Email")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true

                }

                Label {
                    text: qsTr("User Name")
                }
                TextField {
                    id: registerName;

                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true

                    placeholderText: qsTr("Enter Your Name")
                    echoMode: TextInput.NoEcho
                    cursorVisible: true

                }

                Label {
                    text: qsTr("Password")
                }
                TextField {
                    id: registerPassword;

                    placeholderText: qsTr("Enter Your passsword")

                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    echoMode: TextInput.Password
                    cursorVisible: true
                }

                Label {
                    text: qsTr("Repeat password")
                }
                TextField {
                    id: registerPassword2;

                    placeholderText: qsTr("Enter Your passsword again")

                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillWidth: true
                    echoMode: TextInput.Password
                    cursorVisible: true
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

    RowLayout {
        id : bottons
        Button {
            text: qsTr("Cancel")

            onClicked: {
                Qt.quit()
            }

        }

        Item {
            Layout.fillWidth: true
        }

        Button {
            text: tabBar.currentItem.text

            onClicked: {

                const messageIndex = checkData(tabBar.currentIndex);
                if (messageIndex === 0) {

                    if (tabBar.currentIndex) {
                        // register request
                        sigNewUser(registerEmail.text, registerName.text, registerPassword);
                        waitforAnsver();
                    } else {
                        //login request
                        sigLogin(loginEmail.text, loginPass.text);
                        waitforAnsver();
                    }
                } else {
                    errorMessage.text = resultEnum[messageIndex];
                    errorMessage._show();
                }
            }

        }

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

    BasePopUp {
        id: errorMessage;
        property string text: ""
        Label {
            id: sourceText;
            wrapMode: Text.WordWrap
            text: errorMessage.text
            anchors.fill: parent
        }
        backgroundColor: "#ff8f68"
        closeInterval: 10000

        height: 2 * metrix.controlPtMaterial;
        width: 7 * metrix.controlPtMaterial;
        x: 0;
        y: 0;
    }

    onLoginStatusChanged: {
        if (loginStatus === -2)
            busy._show();
        else {
            busy.close();
        }
    }

    PagePopUp {
        id: busy
        modal: true
        autoClose: false;
        clickClose: false;
        BusyIndicator {
            running: loginStatus < 0
            anchors.fill: parent
        }
        height: 2 * metrix.controlPtMaterial
        width: height


    }

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_height:100;anchors_width:100;anchors_x:228;anchors_y:63}
D{i:1;anchors_height:200;anchors_width:200;anchors_x:205;anchors_y:53}D{i:11;anchors_width:240;anchors_x:226;anchors_y:21}
}
 ##^##*/