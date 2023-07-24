import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id:stationSelectItem
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
                    stack.push("qrc:/driverDirectionSelection.qml");
                }
            }
            MenuButton {
                id : buttonSelect
                anchors.right:parent.right
                anchors.top:parent.top
                anchors.bottom:parent.bottom
                width:80
                buttonImageSource : "qrc:/img/busDRMicon.png"
                radius: 1
                imageRatio: 1
                disableButtonClick: false
                buttonText: ""
                onButtonClicked:{
                    dataPoints.selectLine();
                }
            }
            ScrollView {
                    id: stationsArea
                    width: parent.width-(buttonBack.width+buttonSelect.width)
                    anchors.top:parent.top
                    anchors.bottom:parent.bottom
                    anchors.left: buttonBack.right
                    anchors.right:buttonSelect.left
                    clip: true

                    Column {
                        id: columnContainer
                        spacing: 20
                        width: parent.width

                        function createBoxes() {
                            var stations = dataPoints.getStations()

                            function createBox(x, y, text) {
                                var component = Qt.createComponent("MenuButton.qml")
                                if (component.status === Component.Ready) {
                                    var button = component.createObject(columnContainer, {
                                        "x": x,
                                        "y": y,
                                        "buttonText": text,
                                        "width": 600,
                                        "height": 40,
                                        "disableButtonClick": true,
                                        "size": 18,
                                        "radius:" :1.0
                                    })
                                    if (button === null) {
                                        console.log("Error creating button")
                                    }
                                } else {
                                    console.log("Error loading MenuButton.qml")
                                }
                            }

                            var xPosition = 20
                            var yPosition = 0
                            var spacing = 20

                            for (var i = 0; i < stations.length; i++) {
                                createBox(xPosition, yPosition, stations[i])
                                yPosition += 40 + spacing
                            }
                        }

                        Component.onCompleted: createBoxes()
                    }
                }


    }

}
