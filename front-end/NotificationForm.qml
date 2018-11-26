import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Popup {
    id : popup
    width: 200
    height: 100
    x: 0
    y: 0
    transformOrigin: Item.Center

    property bool autoClose: true
    property int closeInterval: 15000;
    property int margin : 0

    NumberAnimation {
        id: animation;
        target: popup
        property: "opacity"
        easing.period: 0.33
        easing.amplitude: 1
        duration: 2000
        easing.type: Easing.OutElastic

        onStopped: {
            if (to < 1)
                close();
        }
    }

    function show(title_, message_, img_) {
        animation.from = 0;
        animation.to = 1;
        animation.start();

        title.text = title_;
        message.text = message_;
        if (img_) {
            image.source = img_;
        } else {
            image.source = "";
        }

        if (autoClose) {
            timerAnimation.start();
        }

        open();
    }

    Timer {
        id: timerAnimation;
        running: false;
        repeat: false;

        onTriggered: {
            animation.from = 1;
            animation.to = 0;
            animation.start();
        }
    }

    onClosed: {
        opacity = 0;
    }

    Page {
        id: page
        title: "Level Up!!!"
        anchors.fill: parent

        Label {
            id: title
            x: 0
            width: 200
            height: 31
            text: qsTr("Title Message")
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            font.pointSize: 14
            fontSizeMode: Text.Fit
            renderType: Text.QtRendering
            textFormat: Text.AutoText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
        }

        RowLayout {
            id: rowLayout
            spacing: 5
            clip: true
            anchors.top: title.bottom
            anchors.topMargin: 1
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            Rectangle {
                color: "#00000000"
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Layout.preferredWidth: rowLayout.height;
                Layout.preferredHeight: rowLayout.height;

                Image {
                    id: image
                    fillMode: Image.PreserveAspectCrop
                    clip: true
                    anchors.fill: parent;
                    source: ""
                }
            }


            Label {
                id: message
                text: qsTr("Message")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillHeight: true;
                Layout.fillWidth: true;
                clip: true
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

}
