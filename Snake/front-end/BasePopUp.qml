import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Popup {
    id : basePopup
    width: 200
    height: 100
    x: 0
    y: 0

    transformOrigin: Item.Center

    property bool autoClose: true
    property int closeInterval: 15000;
    property int margin : 0

    NumberAnimation {
        id: animation;
        target: basePopup
        property: "opacity"
        easing.period: 0.33
        easing.amplitude: 1
        duration: 2000
        easing.type: Easing.OutElastic

        onStopped: {
            if (to < 1)
                close();
        }
    }

    function _show() {
        animation.from = 0;
        animation.to = 1;
        animation.start();

        if (autoClose) {
            timerAnimation.start();
        }

        open();
    }

    Timer {
        id: timerAnimation;
        running: false;
        repeat: false;

        onTriggered: {
            animation.from = 1;
            animation.to = 0;
            animation.start();
        }
    }

    onClosed: {
        if (autoClose)
            opacity = 0;
    }

    closePolicy: (autoClose)? Popup.NoAutoClose: Popup.CloseOnReleaseOutside


}
