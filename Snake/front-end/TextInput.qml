import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3


Item {

    signal close();

    RowLayout {
        anchors.fill: parent
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom

        Label {
            text: qsTr("Write you name ");

        }

        TextField {

            id: input;

            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter

        }

        Button {

            id: ok
            text: qsTr("Ok")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            onClicked: {
                if (contr) {
                    var rec = contr.getRecords()
                    rec.append(input.text, contr.generalLong);
                }

                close();

            }
        }
    }
}
