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
                    stack.pop("qrc:/driverMidArea.qml");

                }
            }
            MenuButton {
                id : buttonUpdate
                anchors.right:parent.right
                anchors.rightMargin:20;
                anchors.bottom:parent.bottom
                anchors.bottomMargin:20;
                width:100
                height:40
                radius: 0.5
                imageRatio: 1
                disableButtonClick: false
                buttonText: "GÜNCELLE"
                onButtonClicked:{
                    dataPoints.updateStations=true;
                }
                z:3
            }
            MenuButton {
                id : buttonTest
                anchors.right:buttonUpdate.left
                anchors.rightMargin:20;
                anchors.bottom:parent.bottom
                anchors.bottomMargin:20;
                width:100
                height:40
                radius: 0.5
                imageRatio: 1
                disableButtonClick: false
                buttonText: "SES TEST"
                onButtonClicked:{
                    dataPoints.playSoundStations="file:///"+dataPoints.getPathAudio(dataPoints.currentStation);
                }
                z:3
            }
            MenuButton {
                id : buttonCancel
                anchors.right:buttonTest.left
                anchors.rightMargin:20;
                anchors.bottom:parent.bottom
                anchors.bottomMargin:20;
                width:100
                height:40
                radius: 0.5
                visible:false
                imageRatio: 1
                disableButtonClick: false
                buttonText: "IPTAL ET"
                onButtonClicked:{
                   dataPoints.cancelLineSelection();
                }
                z:3
            }

            ScrollView {
                id: linesArea
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: buttonBack.right
                anchors.leftMargin:5
                anchors.right: parent.right
                clip: true
                ScrollBar.vertical.interactive: true
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                Grid{
                    id:grid
                    columns: 4
                    spacing: 5

                property bool dataImported: false
                property var createdBoxes: [] // Kutu nesnelerini tutacak dizi


                function clearBoxes() {
                    for (var i = 0; i < createdBoxes.length; i++) {
                        createdBoxes[i].destroy() // Oluşturulmuş kutuları yok et
                    }
                    createdBoxes = [] // Diziyi boşalt
                }

                function createBoxes() {
                    // dataPoints.getLineList() yönteminden hat numaralarını al
                    var lines = dataPoints.getLineList()

                    // Hat numaralarını 2'şerli gruplar halinde bölen bir fonksiyon
                    function chunkArray(arr, size) {
                        var chunkedArr = []
                        for (var i = 0; i < arr.length; i += size) {
                            chunkedArr.push(arr.slice(i, i + size))
                        }
                        return chunkedArr
                    }



                    // Kutu oluşturma fonksiyonu
                    function createBox(text) {
                        var component = Qt.createComponent("MenuButton.qml")
                        if (component.status === Component.Ready) {
                            var button = component.createObject(grid, {
                                "buttonText": text,
                                "width": 180,
                                "height": 80,
                                "disableButtonClick": false,
                                "size": 32,
                                "radius": 1.0
                            })
                            if (button === null) {
                                console.log("Error creating button")
                            } else {
                                button.buttonClicked.connect(function () {
                                    dataPoints.selectviewLine(text);
                                    stack.push("qrc:/StationSelect.qml");
                                })
                                createdBoxes.push(button) // Oluşturulan kutuyu dizide sakla
                            }
                        } else {
                            console.log("Error loading MenuButton.qml")
                        }
                    }
                    var lineChunks = lines;
                    // Kutuların düzenlenmesi
                    var xPosition = 0
                    var yPosition = 0
                    var spacingX = 20
                    var spacingY = 20

                        for (var j = 0; j < lineChunks.length; j++) {
                            createBox(lineChunks[j])
                        }

                }
            }
            }

            Connections {
                target: dataPoints
                onDataImportedChanged: {
                    driverDirectionRectangle.checkIfDataImported();
                }
                onSelectionDoneChanged:{
                    if(dataPoints.selectionDone){
                        buttonCancel.visible=true;
                    }else{
                        buttonCancel.visible=false;
                    }
                }
            }
            Component.onCompleted: {
                driverDirectionRectangle.checkIfDataImported();
            }
            function checkIfDataImported(){
                    grid.clearBoxes()
                    grid.createBoxes()
            }
    }

}
