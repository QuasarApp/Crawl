import QtQuick 2.15
import ViewSolutionsModule 1.0

ListView {
    id: root

    property string selectedLvl: ""

    delegate: ImageView {
        property var data : modelData

        source: data.image
        text: data.name

        width: root.height / 2
        height: root.height * 0.9

        onClicked:  {
            selectedLvl = text
        }
    }
}
