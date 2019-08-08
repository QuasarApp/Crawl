import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12

FrameView {
    id: sideBar
    property int openHeight: 10 * metrix.pt
    property int closedHeight: 1 * metrix.pt
    property int openWidth: 10 * metrix.pt
    property int closedWidth: 1 * metrix.pt

    clip: true;

    property bool resizeWidth: true
    property bool resizeHeight: true

    property bool isOpened: true
    property bool chainAnimation: true
    property var source: null

    readonly property bool openFinished: openHeight === height && openWidth == width;
    readonly property bool closeFinished: closedHeight === height && closedWidth == width;

    function show() {
        if (resizeWidth && !(chainAnimation && resizeHeight))
            width = openWidth;
        if (resizeHeight )
            height = openHeight;

        isOpened = true;

    }

    function hide() {
        if (resizeWidth && !(chainAnimation && resizeHeight))
            width = closedWidth;
        if (resizeHeight )
            height = closedHeight;

        isOpened = false;
    }

    Component.onCompleted: {
        show();
    }

    onHeightChanged: {
        if (isOpened) {
            if (height === openHeight) {
                sideBar.width = openWidth
            }
        }
        else {
            if (height === closedHeight) {
                sideBar.width = closedWidth
            }
        }
    }

    Behavior on width {
        PropertyAnimation {
            duration: 1000
            easing.type: Easing.OutBounce
        }
    }

    Behavior on height {
        PropertyAnimation {
            duration: 1000
            easing.type: Easing.OutBounce
        }


    }


    Item {
        id: sourceVal
        anchors.fill: parent
    }

    onSourceChanged: {
        source.parent = sourceVal;
        source.anchors.fill = sourceVal;
        source.anchors.margins = 0;
        if (source.close) {
            closeConnect.target = source;
        }
    }

}
