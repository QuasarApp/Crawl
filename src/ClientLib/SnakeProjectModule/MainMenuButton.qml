import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

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
