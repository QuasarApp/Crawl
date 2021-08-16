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

    Label {
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 25
        wrapMode: Text.WordWrap
        text: qsTr("Please Select level. If level is not availabel please bue it first.")
    }

    Scene {
        id: scane;
        worldModel: (model)? model.world : null;
        anchors.fill: parent;
    }

    Scene {
        id: nest;
        worldModel: (model)? model.nest : null;
        anchors.fill: parent;
    }

    ToolButton {
        text: "👾"
        font.pixelSize: 35

        onClicked: {
            mainMenuPopUp.open()
        }
        visible: !mainMenuPopUp.visible
    }

    Drawer {
        id: mainMenuPopUp
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        height: parent.height
        width: parent.width / 3

        MainMenu {
            id: mainMenu
            model: (mainWindow.model)? mainWindow.model.menu: null;
            anchors.fill: parent;
        }
    }

    PagePopUp {
        id: settingsPopUp

        source: SettingsView {
            id: settingsView
            model: mainMenu.model ? mainMenu.model.userSettingsModel: null
        }

        standardButtons:  Dialog.Save | Dialog.Cancel | Dialog.RestoreDefaults
        modal: false;
        width: parent.width * 0.8
        height: parent.height * 0.8;

        onAccepted: {
            settingsView.save();
        }

        onReset: {
            settingsView.reset();
        }

        onOpened: {
            settingsView.update();
        }

    }

    PagePopUp {
        id: storePopUp
        source: StoreView {
            id: view
            model: mainMenu.model ? mainMenu.model.storeView: null

        }

        modal: false;
        width: parent.width * 0.8
        height: parent.height * 0.8;

    }

    PagePopUp {
        id: selectLvl
        source: SelectLevelView {
            id: selectLvlView
            model: mainMenu.model ? mainMenu.model.selectLevelModle: null

        }

        modal: false;
        width: parent.width * 0.8
        height: parent.height * 0.8;

    }

    NotificationServiceView {
        anchors.fill: parent;
    }


}
