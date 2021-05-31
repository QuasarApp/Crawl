import QtQuick 2.9

GraphicItem {

    Behavior on color {
        ColorAnimation {
            duration: 2000
        }
    }

    Behavior on radius {
        NumberAnimation {
            duration: 2000
        }
    }

}
