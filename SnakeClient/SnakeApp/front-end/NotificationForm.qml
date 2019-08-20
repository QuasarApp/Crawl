import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

BasePopUp {
    id : popup

    property string text: qsTr("Message")
    property string img: ""
    property string titleText: qsTr("Message")

    autoClose: true;
    closeInterval: 5000

    margins: 0
    spacing: 0

    Page {
        id: page
        anchors.fill: parent

        header: Label {
            text: titleText
            horizontalAlignment: Text.AlignHCenter
        }

        contentItem:
        RowLayout {
            id: rowLayout
            spacing: 5
            clip: true

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
                    source: img
                }
            }


            Label {
                id: message
                text: popup.text
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
