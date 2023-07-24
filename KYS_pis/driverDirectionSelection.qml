import QtQuick 2.15
import QtQuick.Controls 2.15
Item {

    Rectangle {
        id:driverDirectionRectangle

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

            Rectangle {
                id: linesArea
                width: parent.width-buttonBack.width
                anchors.top:parent.top
                anchors.bottom: parent.bottom
                anchors.left : buttonBack.right
                anchors.leftMargin: 20;
                color:"transparent"
                property bool dataImported: false

                // dataImportedChanged sinyali gözlemlemek için signalhandler
                Connections {
                    target: dataPoints
                    onDataImportedChanged: {
                        dataImported = dataPoints.dataImported
                        if (dataImported) {
                            createBoxes()
                        }
                    }
                }
                Component.onCompleted: {
                    dataImported = dataPoints.dataImported
                    if (dataImported) {
                        createBoxes()
                    }
                }



                function createBoxes() {
                        // dataPoints.getLineList() yönteminden hat numaralarını al
                        var lines = dataPoints.getLineList()

                        // Hat numaralarını 10'arlı gruplar halinde bölen bir fonksiyon
                        function chunkArray(arr, size) {
                            var chunkedArr = []
                            for (var i = 0; i < arr.length; i += size) {
                                chunkedArr.push(arr.slice(i, i + size))
                            }
                            return chunkedArr
                        }

                        var lineChunks = chunkArray(lines, 6)

                        // Kutu oluşturma fonksiyonu
                        function createBox(x, y, text) {
                            var component = Qt.createComponent("MenuButton.qml")
                            if (component.status === Component.Ready) {
                                var button = component.createObject(linesArea, {
                                    "x": x,
                                    "y": y,
                                    "buttonText": text,
                                    "width": 100,
                                    "height": 40,
                                    "disableButtonClick": false,
                                    "size" : 18,
                                    "radius:" :1.0
                                })
                                if (button === null) {
                                    console.log("Error creating button")
                                }else{
                                    button.buttonClicked.connect(function(){
                                        dataPoints.selectviewLine(text);
                                        stack.push("qrc:/StationSelect.qml");
                                    }
                                        )
                                }
                            } else {
                                console.log("Error loading MenuButton.qml")
                            }
                        }

                        // 10 adet kutuyu oluştur
                        var xPosition = 0
                        var yPosition = 0
                        var spacing = 20

                        for (var i = 0; i < lineChunks.length; i++) {
                            var chunk = lineChunks[i]

                            for (var j = 0; j < chunk.length; j++) {
                                createBox(xPosition, yPosition, chunk[j])
                                xPosition += 100 + spacing
                            }

                            xPosition = 0
                            yPosition += 40 + spacing
                        }
                    }
            }


    }

}
