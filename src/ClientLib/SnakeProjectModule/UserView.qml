import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12


Flickable {
    id: userVewFlic

    contentWidth: userVew.width
    contentHeight: userVew.height
    flickableDirection: Flickable.VerticalFlick;
    property var model: null
    signal tryConnect();

    ScrollBar.vertical: ScrollBar {
        width: metrix.pt
    }

    Item {
        id: userVew

        width: userVewFlic.width

        ColumnLayout {
            id: columnLayout
            anchors.fill: parent

            visible: (model)? !model.offline: false;

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

        ColumnLayout {
            visible: (model)? model.offline: false;
            anchors.fill: parent

            Label {
                wrapMode: Text.WordWrap
                Layout.fillWidth: true

                text: qsTr("Offline mode. Your statistics will be frozen until you login your profile.");
            }

            Button {
                text: qsTr("try conect to server ");

                Layout.alignment: Qt.AlignHCenter

                onClicked: {
                    tryConnect();
                }
            }

            Item {
                Layout.fillHeight: true

            }
        }

    }
}

