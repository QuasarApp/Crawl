import QtQuick
import CrawlModule
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls

DefaultMenu {
    columns: 2
    rows: 2
    
    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.columnSpan: 2
        Layout.rowSpan: 2
        
        color: "#22000000"
        
        MouseArea {
            property bool track: false
            property real oldX: 0
            property real oldY: 0
            cursorShape: Qt.DragMoveCursor
            onPressed: (mouse) => {
                           track = true
                           oldX = mouse.x
                           oldY = mouse.y
                           
                       }
            
            onReleased: {
                track = false
            }
            
            onPositionChanged: (mouse) => {
                                   if (!model) {
                                       return;
                                   }
                                   
                                   if (!track) {
                                       return;
                                   }
                                   
                                   let delta = mouse.y - oldY;
                                   let radianDelta = (delta / (parent.height / 2)) * 45

                                   model.xChanged(radianDelta)
                                   oldY = mouse.y;

                                   
                                   delta = mouse.x - oldX;
                                   radianDelta = (delta / (parent.width / 2)) * 45
                                   model.yChanged(radianDelta)
                                   oldX = mouse.x;


                               }
            
            anchors.fill: parent
        }
    }
    
    
}
