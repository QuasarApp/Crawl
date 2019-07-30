import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12

Frame {
    id: userVew

    property var model: null
    property int sourceId: 0
    width: 5 * metrix.pt
    background: Rectangle {
        color: "#50ffffff"
        border.color: "#5e5d5d"
        radius:  4
    }

    padding: 10


    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        ImageView {
            drawItem: "image://userItems/player/" + ((model)? model.id: -1).toString()
            Layout.fillWidth: true
            Layout.fillHeight: true

        }

        PropertyView {
            Layout.fillWidth: true
            keyText: qsTr("You ");
            valueText : (model)? model.name: -1

        }

        PropertyView {
            valueText : ((model)? model.gmail: -1).toString()
            Layout.fillWidth: true
            keyText: qsTr("You gmail");
        }

        PropertyView {
            keyText: qsTr("Money ");

            valueText : ((model)? model.money: -1).toString()
            Layout.fillWidth: true
        }

        PropertyView {
            keyText: qsTr("Record ");

            valueText : ((model)? model.record: -1).toString()
            Layout.fillWidth: true
        }

        PropertyView {
            keyText: qsTr("AvgRecord ");

            valueText : ((model)? model.avgRecord: -1).toString()
            Layout.fillWidth: true

        }

        PropertyView {
            keyText: qsTr("Snake ");

            valueImage : "image://userItems/item/" + ((model)? model.cureentSnake: -1).toString()
            Layout.fillWidth: true

        }
    }


}
