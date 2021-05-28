import QtQuick
import QtQuick.Controls

import QtQuick.Layouts


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
