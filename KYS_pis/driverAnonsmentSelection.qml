import QtQuick 2.15
import QtQuick.Controls 2.15

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
                stack.pop("qrc:/driverMidArea.qml");
            }
        }
        ScrollView {
                id: stationsArea
                width: parent.width-(buttonBack.width)
                anchors.top:parent.top
                anchors.bottom:parent.bottom
                anchors.left: buttonBack.right
                anchors.right:parent.right
                clip: true


                    function createBoxes() {
                        var anounces = dataPoints.getAnounceList("C:/appKYS_Pis/PISSpecialAnounce")

                        function chunkArray(arr, size) {
                            var chunkedArr = []
                            for (var i = 0; i < arr.length; i += size) {
                                chunkedArr.push(arr.slice(i, i + size))
                            }
                            return chunkedArr
                        }

                        var lineChunks = chunkArray(anounces, 2)

                        var buttonWidth = (stationsArea.width/2)*0.4
                        var buttonHeight = (stationsArea.height/4)*.7
                        function createBox(x, y, text) {
                            var rectWidth = (stationsArea.width/2)*.9;
                            var rectHeight = (stationsArea.height/4)*.9;
                            var rect = Qt.createQmlObject(
                                "import QtQuick 2.15; Rectangle {
                                width: " + rectWidth + ";
                                height: " + rectHeight + ";
                                color: 'grey';
                                opacity: 0.6;
                                x: "+x+";
                                y: "+y+";}",
                                stationsArea
                            );

                            var component = Qt.createComponent("MenuButton.qml")
                            if (component.status === Component.Ready) {
                                var button = component.createObject(rect, {
                                    "buttonText": "OYNAT",
                                    "width": buttonWidth,
                                    "height": buttonHeight,
                                    "disableButtonClick": false,
                                    "size": 18,
                                    "radius": 1.0
                                })
                                if (button === null) {
                                    console.log("Error creating button")
                                } else {
                                    button.buttonClicked.connect(function() {
                                         dataPoints.playSound="file:///C:/appKYS_Pis/PISSpecialAnounce/" + text + ".mp3"

                                    })
                                }

                                var switchItem = Qt.createQmlObject(
                                    "import QtQuick.Controls 2.15; Switch { }",
                                    rect
                                );


                                var textItem = Qt.createQmlObject(
                                   "import QtQuick 2.15; Text {
                                    text: '" + text + "';
                                    color: 'white'
                                    style: Text.Normal
                                    focus: false
                                    font.weight: Font.Bold
                                    font.family: 'Verdana'
                                    font.pixelSize: 12}",
                                    rect
                                );

                                textItem.anchors.left = rect.left;
                                textItem.anchors.top = rect.top;
                                textItem.anchors.leftMargin = 5;
                                textItem.anchors.topMargin = 1;

                                button.anchors.verticalCenter = rect.verticalCenter;
                                button.anchors.right = rect.right;
                                button.anchors.rightMargin = 5;
                                switchItem.anchors.verticalCenter = rect.verticalCenter;
                                switchItem.anchors.left = rect.left;
                                switchItem.anchors.leftMargin = 10;
                                switchItem.checked = false; // Switch'in durumunu kendiniz ayarlayacaksınız.


                            } else {
                                console.log("Error loading MenuButton.qml")
                            }
                        }

                        var xPosition = 20
                        var yPosition = 0
                        var spacing = 5


                        for (var i = 0; i < lineChunks.length; i++) {
                            var chunk = lineChunks[i]

                            for (var j = 0; j < chunk.length; j++) {
                                createBox(xPosition, yPosition, chunk[j])
                                xPosition += (stationsArea.width/2) + spacing
                            }

                            xPosition = 20
                            yPosition += (stationsArea.height/4) + spacing
                        }
                    }


                    Component.onCompleted: createBoxes()

            }



    }
}
