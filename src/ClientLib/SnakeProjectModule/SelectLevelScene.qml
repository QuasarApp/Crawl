import QtQuick
import QtQuick.Controls

import QtQuick.Layouts

Item {
    id: item1

    GridLayout {
        id: gridLayout
        rows: 8
        columnSpacing: 5
        rowSpacing: 5
        anchors.rightMargin: 200
        anchors.leftMargin: 200
        anchors.bottomMargin: 100
        anchors.topMargin: 50
        anchors.fill: parent
        columns: 8

        RoundButton {
            id: roundButton
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "1"
        }

        RoundButton {
            id: roundButton1
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "2"
        }

        RoundButton {
            id: roundButton2
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "3"
        }

        RoundButton {
            id: roundButton3
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "4"
        }

        RoundButton {
            id: roundButton4
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "5"
        }

        RoundButton {
            id: roundButton5
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "6"
        }

        RoundButton {
            id: roundButton6
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "7"
        }

        RoundButton {
            id: roundButton7
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "8"
        }

        RoundButton {
            id: roundButton8
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "9"
        }

        RoundButton {
            id: roundButton9
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "10"
        }

        RoundButton {
            id: roundButton10
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "11"
        }

        RoundButton {
            id: roundButton11
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "12"
        }

        RoundButton {
            id: roundButton12
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "13"
        }

        RoundButton {
            id: roundButton13
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "14"
        }

        RoundButton {
            id: roundButton14
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "15"
        }

        RoundButton {
            id: roundButton15
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "16"
        }

        RoundButton {
            id: roundButton16
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "17"
        }

        RoundButton {
            id: roundButton17
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "18"
        }

        RoundButton {
            id: roundButton18
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "19"
        }

        RoundButton {
            id: roundButton19
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "20"
        }

        RoundButton {
            id: roundButton20
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "21"
        }

        RoundButton {
            id: roundButton21
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "22"
        }

        RoundButton {
            id: roundButton22
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "23"
        }

        RoundButton {
            id: roundButton23
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "24"
        }

        RoundButton {
            id: roundButton24
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "25"
        }

        RoundButton {
            id: roundButton25
            width: 10*mainWindow.point
            height: 10*mainWindow.point
            text: "26"
        }
    }

    Label {
        id: label
        x: 187
        color: "#795548"
        text: qsTr("Select Level")
        font.bold: true
        font.pixelSize: 30
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
    }

}

