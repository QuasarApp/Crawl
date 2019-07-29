import QtQuick 2.13
import QtQuick.Controls.Material 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3

Item {
    id: userVew

    property var model: null
    property int sourceId: 0

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        ImageView {
            drawItem: "image://userItems/" + ((model)? model.id: -1).toString()
        }

    }

}
