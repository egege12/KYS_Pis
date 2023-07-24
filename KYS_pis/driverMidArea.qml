import QtQuick 2.15
import QtQuick.Controls 2.15
    Rectangle {
        anchors.fill: parent
        color:"transparent"
        Item{
            anchors.left:parent.left
            anchors.top:parent.top
            anchors.bottom: parent.bottom
            width: parent.width/2

            MenuButton {
                id : buttonAnounces
                anchors.left:parent.left
                anchors.top:parent.top
                anchors.bottom:parent.bottom
                anchors.right:parent.right
                anchors.margins: 15
                buttonImageSource : "qrc:/img/anonunceIcon.png"
                radius: 1
                disableButtonClick: false
                buttonText: "Anonslar"
                onButtonClicked:{
                    stack.push("driverAnonsmentSelection.qml");
                }
            }
        }
        Popup{
            id:popupWindow
            spacing :5
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
            focus: true
            modal:true
            anchors.centerIn: parent

            PopupWindow{
                id:windowElement
                onButtonClicked:popupWindow.close();
            }
        }
        Item{
            anchors.right:parent.right
            anchors.top:parent.top
            anchors.bottom: parent.bottom
            width: parent.width/2

            MenuButton {
                id : buttonDirections
                anchors.left:parent.left
                anchors.top:parent.top
                anchors.bottom:parent.bottom
                anchors.right:parent.right
                anchors.margins: 15
                buttonImageSource : "qrc:/img/busDRMicon.png"
                radius: 1
                disableButtonClick: false
                buttonText: "Hat Seçimi"
                onButtonClicked:{
                    stack.push("driverDirectionSelection.qml");
                }
            }
        }
        Connections{
            target:dataPoints
            onConfirmPopup: {
                popupWindow.open();
                windowElement.textMessage = dataPoints.getStationName(dataPoints.confirmStationID())+" istasyonundan mı başlamak istersiniz?"
            }
        }
    }

