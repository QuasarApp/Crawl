import QtQuick
import ViewSolutionsModule
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Page {
    id: root
    property var model: null;
    ColumnLayout {
        anchors.fill: parent
        ListView {
            id: listView
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: root.model
            delegate: delegateRow
            clip: true

            Component {
                id: delegateRow

                RowLayout {
                    width: listView.width
                    height: 100
                    Image {
                        id: img
                        fillMode: Image.PreserveAspectCrop
                        source: itemImage
                        Layout.fillHeight: true
                        Layout.preferredWidth: height * 2
                    }

                    Label {
                        text: itemName
                        Layout.fillHeight: true
                    }

                    Label {
                        text: itemDescription
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }

                    CheckBox {
                        id: buyStatus
                        tristate: false
                        checkState: (itemWasBuy)? Qt.Checked: Qt.Unchecked
                        enabled: false
                    }

                    Button {
                        text: qsTr("Buy");
                        visible: !itemWasBuy

                        onClicked: () => {
                                   }
                    }
                }
            }
        }
    }
}
