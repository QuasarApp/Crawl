import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12

Frame {
    id: frameVew
    background: Rectangle {
        color: (Material.theme == Material.Dark)? "#50000000": "#50ffffff"
        border.color: "#5e5d5d"
        radius:  metrix.mm
    }

    padding: 3 * metrix.mm
}
