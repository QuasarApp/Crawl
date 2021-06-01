import QtQuick

Item {
    property var model: null
    property int guiId: (model) ? model.guiId : -1;
}
