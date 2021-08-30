import QtQuick
import ViewSolutionsModule
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Page {
    id: store
    property var model: null;
    ColumnLayout {
        anchors.fill: parent
        ListView {
            id: listView
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: store.model
            delegate: delegateRow
            clip: true

            Component {
                id: delegateRow

                Rectangle {
                    width: listView.width
                    height: 100
                    color: (itemId === store.model.currentLevel) ? "#ffaf2c": "#00000000"

                    Behavior on color {

                        ColorAnimation {
                            duration: 200
                        }
                    }

                    RowLayout {

                        anchors.fill: parent

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

                        Button {
                            text: qsTr("Select");
                            visible: itemId !== store.model.currentLevel

                            onClicked: () => {
                                            if (store.model)
                                                store.model.select(itemId);
                                       }
                        }
                    }
                }

            }
        }
    }
}
