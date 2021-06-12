import QtQuick 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls 2.15

AbstractMenuView {
    Button {
        text: qsTr("Back to menu.")
        onClicked: {
            if (model) {
                model.backToMenu()
            }
        }
    }
}
