import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12

Frame {
    id: frameVew
    property bool translucent: true
    property bool showBorder: true

    function _backGroundColor() {
        if (translucent) {
            if (Material.theme == Material.Dark) {
                return "#50000000";
            }

            return "#50ffffff";
        }

        return Material.background;
    }

    background: Rectangle {
        color: _backGroundColor()
        border.color: (Material.theme == Material.Dark)? "#000000": "#cfcfcf"
        border.width:  (showBorder)? 1 : 0
        radius: metrix.mm
    }

    padding: 3 * metrix.mm
}
