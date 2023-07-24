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
                property string stationID;
                onButtonClicked:{
                    dataPoints.confirmStationSelection(windowElement.stationID);
                    popupWindow.close();
                }
                onPlusClicked:{
                    dataPoints.increaseConfirmationStation();
                }
                onMinusClicked:{
                    dataPoints.deacreaseConfirmationStation();
                }
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
                if(!popupWindow.opened){
                    popupWindow.open();
                }
                windowElement.textMessage = "Yukarıdaki istasyondan mı başlıyorsunuz?"
                windowElement.stationID = dataPoints.confirmStationID
                windowElement.stationText = dataPoints.getStationName(windowElement.stationID)
            }
        }
        Connections{
            target:dataPoints
            onConfirmStationIDChanged: {
                windowElement.stationID = dataPoints.confirmStationID
                windowElement.stationText = dataPoints.getStationName(windowElement.stationID)
            }
        }
    }

