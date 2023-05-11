import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    visible: true
    width: 1920
    height: 540
    color: "white"
    x: Screen.desktopAvailableWidth (2)
    y: Screen.desktopAvailableHeight(2)
    Loader {
            id: secondaryLoader
            source: "secondary.qml"
            visible: true
            active: true
        }
    Rectangle {
        anchors.right:parent.right
        anchors.top:parent.top
        width: parent.width/2
        height: 540
        color: "white"
    }
}
