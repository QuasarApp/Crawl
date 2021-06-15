//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

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
