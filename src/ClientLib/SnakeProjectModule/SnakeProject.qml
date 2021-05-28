import QtQuick
import QtQuick.Window
import QtQuick.Controls

import NotifyModule

ApplicationWindow {
    id: mainWindow;
    visible: true;
    width: 640;
    height: 480;
    title: qsTr("SnakeOnTheRoad");

    Metrix {id: metrix}

    Scene {
        id: scane;
        model: contr;
        anchors.fill: parent;
    }

    MainMenu {

        model: (contr)? contr.mainMenuModel: null;
        anchors.fill: parent;
        visible: scane.showMenu;

        onPlayGame: {
            contr.showMenu = false;
        }

    }

    NotificationServiceView {
        anchors.fill: parent;
    }
}
