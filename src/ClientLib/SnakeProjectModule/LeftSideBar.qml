import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

SideBar {
    id: leftSideBar
    anchors.left: parent.left;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    closedWidth: closeButton.width + padding * 2;
    openWidth: 10 * metrix.pt;
    resizeHeight: false;

    header:
        RowLayout {

        Button {
            id: closeButton
            text: leftSideBar.isOpened? "<" : ">"

            Layout.preferredHeight: metrix.controlPtMaterial;
            Layout.preferredWidth: metrix.controlPtMaterial;

            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            onClicked: {
                if (leftSideBar.isOpened)
                    leftSideBar.hide();
                else
                    leftSideBar.show();
            }

        }
    }
}
