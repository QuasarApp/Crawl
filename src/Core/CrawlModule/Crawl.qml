//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick
//import QtQuick.Window
import QtQuick.Controls

import NotifyModule

ApplicationWindow {
    id: mainWindow;
    visible: true;
    width: 1024;
    height: 720;
    title: qsTr("Crawl");

    property var model: engine

    Metrix {id: metrix}

    Scene {
        id: scane;
        worldModel: (model)? model.world : null;
        anchors.fill: parent;
    }

    Scene {
        id: nest;
        worldModel: (model)? model.world : null;
        anchors.fill: parent;
    }

    StoreView {
        model: (mainWindow.model)? mainWindow.model.storeView: null
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
