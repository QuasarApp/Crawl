import QtQuick
import QtQuick.Controls

import QtQuick.Layouts

Dialog {
    id : basePopup
    width: 200
    height: 100
    x: 0
    y: 0

    transformOrigin: Item.Center

    property bool autoClose: true
    property bool clickClose: true

    property int closeInterval: 15000;
    property int margin : 0

    function _show() {

        if (autoClose) {
            timerAutoClose.start();
        }

        open();
    }

    Timer {
        id: timerAutoClose;
        running: false;
        repeat: false;
        interval: closeInterval;

        onTriggered: {
            close();
        }
    }

    onClosed: {
        if (autoClose)
            opacity = 0;
    }

    closePolicy: (!clickClose || autoClose)? Popup.NoAutoClose: Popup.CloseOnReleaseOutside

    onRejected: close()

}
