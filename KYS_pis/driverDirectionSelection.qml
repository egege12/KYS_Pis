import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    Rectangle {
        anchors.fill: parent
        color:"transparent"

            MenuButton {
                id : buttonBack
                anchors.left:parent.left
                anchors.top:parent.top
                anchors.bottom:parent.bottom
                width:50
                buttonImageSource : "qrc:/img/back.png"
                radius: 1
                imageRatio: 1
                disableButtonClick: false
                buttonText: ""
                onButtonClicked:{
                    stack.push("qrc:/driverMidArea.qml");
                }
            }

    }
}
