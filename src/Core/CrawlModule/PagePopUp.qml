//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

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
