import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

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

                source: "qrc:/logo/logo"
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

                text: qsTr("Управление игрой происходит посредством нажатия на тачпад вашего устройства, чем чаще нажимаете, тем быстрее двигается змейка. Каждое последующее нажатие, изменяет направление змейки, в противоположную сторону.
Цель игры набрать максимальное количество очков. Количество очков зависит от пройденного расстояния. \n
Автор: Янкович Роман. Группа 10903516");
                anchors.fill: parent
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
