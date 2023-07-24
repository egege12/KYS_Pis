import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
Item {
    id: popupWarning
    property var textMessage;
    property var stationText;
    signal escapedClicked;
    signal buttonClicked;
    signal plusClicked;
    signal minusClicked;
    Frame {
        id: frameWarning
        Rectangle{
            id:rectWarning
            width: 600
            height: 400
            border.color: "#636363"
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#fdfbfb"
                }
                GradientStop {
                    position: 1
                    color: "#ebedee"
                }
                orientation: Gradient.Vertical
            }
            anchors.centerIn: parent
            RowLayout {
                id: rowLayoutWarning
                anchors.fill: parent
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.bottomMargin: 10
                anchors.topMargin: 10
            }

            Text {
                id: textStation
                text: popupWarning.stationText
                width: 250
                height: 77
                anchors.top:parent.top
                anchors.topMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideLeft
                font.pixelSize: 32
                font.family: "Verdana"
                wrapMode: "WordWrap"
            }
            Text {
                id: textDetailWarning
                text: popupWarning.textMessage
                width: 250
                height: 77
                anchors.centerIn: parent
                elide: Text.ElideLeft
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 22
                font.family: "Verdana"
                wrapMode: "WordWrap"
            }
            MenuButton {
                id : buttonMinus
                width: 100
                height: 100
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                buttonImageSource : "qrc:/img/minus.png"
                radius: 1
                disableButtonClick: false
                buttonText: "Anonslar"
                onButtonClicked:{popupWarning.minusClicked()
                }
            }
            MenuButton {
                id : buttonPlus
                width: 100
                height: 100
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                buttonImageSource : "qrc:/img/plus.png"
                radius: 1
                disableButtonClick: false
                buttonText: "Anonslar"
                onButtonClicked:{popupWarning.plusClicked()
                }
            }
            DelayButton {
                id: buttonWarning
                width: 130
                height: 80
                anchors.bottom:parent.bottom
                anchors.bottomMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("ONAYLA")
                font.bold: true
                font.pixelSize: 20
                onActivated: popupWarning.buttonClicked();
            }
        }
    }

}
