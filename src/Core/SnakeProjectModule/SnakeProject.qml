import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import NotifyModule 1.0

ApplicationWindow {
    id: mainWindow;
    visible: true;
    width: 640;
    height: 480;
    title: qsTr("SnakeProject");

    Metrix {id: metrix}

    Scene {
        id: scane;
        model: engine;
        anchors.fill: parent;
    }

    MainMenu {

        model: (mainmenu)? mainmenu: null;
        anchors.fill: parent;
        visible: scane.showMenu
    }

    NotificationServiceView {
        anchors.fill: parent;
    }
}
