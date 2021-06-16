//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

import QtQuick 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Button {
    id: exit
    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    font.pixelSize: height * 0.1
    display: AbstractButton.TextBesideIcon
    spacing: 4
    focusPolicy: Qt.StrongFocus

    Layout.preferredHeight: parent.height / (parent.rows + 1)
    Layout.preferredWidth: parent.width / (parent.columns + 1)

}
