import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: pagePopUp
    property var source: null

    Item {
        id: sourceVal
        anchors.fill: parent
    }

    onSourceChanged: {
        if (!source)
            return;

        source.parent = sourceVal;
        source.anchors.fill = sourceVal;
    }

    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2
}
