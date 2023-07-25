import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia 5.15
import QtQml.Models 2.2
import Qt.labs.folderlistmodel 2.15
Item {
    Rectangle {
        id:rectangleAnonuncement
        anchors.fill: parent
        color:"transparent"
        property bool announcement_priorty : false;
        property bool anouncement_next_station: false;
        property bool anouncement_current_station: false;


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
                        var anounces = dataPoints.getAnounceList("C:/appKYS_Pis/PISSpecialAnounce")

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
        MediaPlayer {
            id: playerSound
            onStatusChanged: {
                if (playerSound.mediaStatus == MediaPlayer.EndOfMedia) {
                    playerSound.source = ""
                }
            }
            onSourceChanged: {
                playerSound.play();
            }

        }
        Audio{
            id:audio
            source:playerSound
        }


    }
}
