import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: mainWindow;
    visible: true;
    width: 1140;
    height: 540;
    title: qsTr("SnakeOnTheRoad");

    Component.onCompleted: {
        mainWindow.showFullScreen();
    }

    readonly property int pointCount: 100;

    property real point: (width < height) ? width/pointCount : height/pointCount;
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
            scane.showMenu = false;
        }

    }
}
