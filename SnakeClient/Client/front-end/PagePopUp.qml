import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

BasePopUp {
    id: pagePopUp
    property string source: ""
    autoClose: false

    Loader {
        id: sour
        anchors.fill: parent
        source: (pagePopUp.source)? pagePopUp.source: "Item.qml";

        Connections {
            target: sour.item
            onClose: {
                pagePopUp.close();
            }
        }
    }
}
