import QtQuick
import QtQuick.Controls

import QtQuick.Layouts

BasePopUp {
    id: pagePopUp
    property var source: null
    autoClose: false

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
