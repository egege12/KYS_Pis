import QtQuick 2.15

Rectangle {
    id:buttonRectangle
    signal buttonClicked()
    signal buttonReleased()
    signal buttonEntered()
    signal buttonExited()
    property string buttonImageSource: ""
    property bool disableButtonClick
    property real buttonOpacity : 0.6
    property color disabledColor : "#9e9b9b"
    property color pressedColor : "#575757"
    property color releasedColor : "#707070"
    property color hoveredColor : "#575757"
    property real imageRatio : 0.8
    property string buttonText: ""
    property real size : 12
    height: width
    radius: 1
    opacity : buttonRectangle.buttonOpacity
    onDisableButtonClickChanged: disableButtonClick ? disabledColor : releasedColor
    color :disableButtonClick ? disabledColor : releasedColor
    Image{
        id:image
        width: parent.width*imageRatio
        height: parent.height*imageRatio
        anchors.centerIn: parent
        antialiasing: true
        source: parent.buttonImageSource
        opacity: parent.disableButtonClick ? 0.5 : 1.0
        fillMode:Image.PreserveAspectFit
    }
    Text{
        id:text
        anchors.top: buttonImageSource!=""? (image.bottom) : parent.top
        anchors.topMargin:5
        anchors.horizontalCenter: parent.horizontalCenter
        text:buttonText
        font.pixelSize: buttonImageSource!=""? (25) : size
        elide: Text.ElideLeft
        antialiasing: true
        font.hintingPreference: Font.PreferNoHinting
        style: Text.Normal
        focus: false
        font.weight: Font.Bold
        font.family: "Verdana"
        color: "white"
    }

    MouseArea{
        id:mouseArea
        anchors.fill: parent
        onPressed: parent.color = parent.disableButtonClick ? parent.disabledColor : parent.pressedColor
        onReleased: {
            parent.color = parent.disableButtonClick ? parent.disabledColor : parent.releasedColor
            parent.disableButtonClick ? undefined : parent.buttonReleased()
        }
        onClicked: parent.disableButtonClick ? undefined: parent.buttonClicked()
        hoverEnabled: false
        onEntered: {parent.color = parent.hoveredColor; parent.buttonEntered()}
        onExited: {parent.color = parent.releasedColor; parent.buttonExited()}

    }
}
