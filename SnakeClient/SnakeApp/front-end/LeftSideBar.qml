import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12

SideBar {
    id: leftSideBar

    property alias button : closeButton

    anchors.left: parent.left;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    closedWidth: closeButton.width;
    openWidth: 10 * metrix.pt;
    resizeHeight: false;


    Button {
        id: closeButton
        text: leftSideBar.isOpened? "<" : ">"

        height: metrix.controlPtMaterial;
        width: metrix.controlPtMaterial;

        anchors.right: parent.right;
        anchors.top:  parent.top;

        anchors.rightMargin: -leftSideBar.padding;
        anchors.topMargin:  -leftSideBar.padding;

        onClicked: {
            if (leftSideBar.isOpened)
                leftSideBar.hide();
            else
                leftSideBar.show();
        }

    }
}
