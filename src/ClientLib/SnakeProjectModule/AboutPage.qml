import QtQuick
import QtQuick.Controls

import QtQuick.Layouts

Item {
    clip: true
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.preferredHeight: parent.width / 4
            Layout.preferredWidth: parent.width / 4
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            color: "#00000000"
            Image {
                id: aboutLogo
                fillMode: Image.PreserveAspectFit

                source: "qrc:/images/res/logo.png"
                anchors.margins: 10
                anchors.fill: parent

            }
        }



        Flickable {
            id: flickable
            clip: true
            flickableDirection: Flickable.VerticalFlick

            Layout.preferredHeight: parent.height - parent.height / 2.8


            TextArea.flickable: TextArea {
                id: textArea
                textFormat: Qt.RichText
                wrapMode: TextArea.Wrap
                readOnly: true
                persistentSelection: true

                leftPadding: 6
                rightPadding: 6
                topPadding: 0
                bottomPadding: 0
                background: null

                text: qsTr("Product of QuasarrApp");
                font.family: "Verdana"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop

                onLinkActivated: Qt.openUrlExternally(link)
            }

            ScrollBar.vertical: ScrollBar { }
            Layout.fillWidth: true

        }

    }

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
