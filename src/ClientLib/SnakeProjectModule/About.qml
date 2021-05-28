import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {

    signal close();

    title: "Page"
    header: Rectangle {
        height: parent.height * 0.1
        color: "#cccccc"
        Label {
            id: title
            text: qsTr("About")
            font.pointSize: 13
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent;
            anchors.margins: 5
        }
    }

    contentItem: AboutPage{
    }

}
