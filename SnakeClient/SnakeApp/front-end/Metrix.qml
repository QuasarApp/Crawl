import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.3

Item {
    property real mm: Screen.pixelDensity
    property real sm: 10 * mm
    readonly property real dsm: Math.sqrt(Math.pow(Screen.desktopAvailableWidth, 2) + Math.pow(Screen.desktopAvailableHeight, 2)) / sm
    property real pt: getfactor(dsm) * sm
    property real controlPtMaterial: Material.buttonHeight

    function getfactor(dsm) {
        if (dsm < 30) {
            return 0.5
        } else if ( dsm < 70) {
            return 1
        } else if (dsm < 140) {
            return 2;
        } else
            return 4;
    }
}
