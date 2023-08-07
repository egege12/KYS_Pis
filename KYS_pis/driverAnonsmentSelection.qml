import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml.Models 2.2
import Qt.labs.folderlistmodel 2.15

Item {
    Rectangle {
        id: rectangleAnonuncement
        anchors.fill: parent
        color: "transparent"
        property bool announcement_priorty: false;
        property bool anouncement_next_station: false;
        property bool anouncement_current_station: false;

        MenuButton {
            id: buttonBack
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 50
            buttonImageSource: "qrc:/img/back.png"
            radius: 1
            imageRatio: 1
            disableButtonClick: false
            buttonText: ""
            onButtonClicked: {
                stack.pop("qrc:/driverMidArea.qml");
            }
        }

        FolderListModel {
            id: folderModelAnounce
            folder: "file:///C:/appKYS_Pis/PISSpecialAnounce"
            nameFilters: ["*.mp3"]
        }
        ScrollView {
            id: stationsArea
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
                columns: 2
                spacing: 5

                 property var createdBoxes: [] // Kutu nesnelerini tutacak dizi


                function createBox(text) {
                    var rectWidth = (stationsArea.width / 2);
                    var rectHeight = (stationsArea.height / 4) ;
                    var rect = Qt.createQmlObject(
                        "import QtQuick 2.15; Rectangle { width: " + rectWidth + "; height: " + rectHeight + "; color: 'grey'; opacity: 0.6;}",
                        grid // Add the Rectangle as a child of the Column
                    );

                    var component = Qt.createComponent("MenuButton.qml")
                    if (component.status === Component.Ready) {
                        var button = component.createObject(rect, {
                            "buttonText": "OYNAT",
                            "width": rectWidth * 0.4,
                            "height": rectHeight * 0.7,
                            "disableButtonClick": false,
                            "size": 18,
                            "pressedColor": "#DCECF5",
                            "radius": 1.0
                        })

                        if (button === null) {
                            console.log("Error creating button")
                        } else {

                            button.buttonText = (("file:///C:/appKYS_Pis/PISSpecialAnounce/" + text + ".mp3") === dataPoints.playSound) ? "DURDUR" : "OYNAT";

                            button.buttonClicked.connect(function() {
                                if (button.buttonText === "DURDUR") {
                                    dataPoints.playSound = "";
                                } else {
                                    dataPoints.playSound = "file:///C:/appKYS_Pis/PISSpecialAnounce/" + text + ".mp3";
                                }
                            });


                            dataPoints.playSoundChanged.connect(function() {
                                button.buttonText = (("file:///C:/appKYS_Pis/PISSpecialAnounce/" + text + ".mp3") === dataPoints.playSound) ? "DURDUR" : "OYNAT";
                            });
                        }

                        var switchItem = Qt.createQmlObject(
                            "import QtQuick.Controls 2.15; Switch { }",
                            rect
                        );
                        switchItem.onClicked.connect(function(){
                            if(switchItem.checked){
                                dataPoints.addPeriodicAnounceList(text);
                            }else{
                                dataPoints.removePeriodicAnounceList(text);
                            }

                        });
                        switchItem.anchors.verticalCenter = rect.verticalCenter;
                        switchItem.anchors.left = rect.left;
                        switchItem.anchors.leftMargin = 10;
                        switchItem.checked = false;
                        var textItem = Qt.createQmlObject(
                           "import QtQuick 2.15; Text { text: '" + text + "'; color: 'white'; style: Text.Normal; focus: false; font.weight: Font.Bold; font.family: 'Verdana'; font.pixelSize: 12}",
                            rect
                        );
                        textItem.anchors.left = rect.left;
                        textItem.anchors.stop = rect.top;
                        textItem.anchors.leftMargin = 5;
                        textItem.anchors.topMargin = 1;
                        var comboBox = Qt.createQmlObject(
                                    "import QtQuick.Controls 2.15; ComboBox { }",
                                    rect
                                );
                        comboBox.width = 100;
                        comboBox.height = 30;
                        comboBox.anchors.left = switchItem.right; // ComboBox'ı button'un sol tarafına yerleştirin
                        comboBox.anchors.leftMargin = 5;
                        comboBox.anchors.verticalCenter = rect.verticalCenter;
                        comboBox.model = [
                            "30 Dakika",
                            "45 Dakika",
                            "1 Saat",
                            "2 Saat",
                            "3 Saat",
                            "Günde 1"
                        ];
                        comboBox.onActivated.connect(function(){
                            comboBox.displayText=comboBox.currentText;
                            dataPoints.setPeriodofAnounceList(text,comboBox.currentText);
                        });
                        comboBox.displayText=dataPoints.getPeriodofAnounceList(text);
                        button.anchors.verticalCenter = rect.verticalCenter;
                        button.anchors.right = rect.right;
                        button.anchors.rightMargin = 5;
                        createdBoxes.push(rect);
                    } else {
                        console.log("Error loading MenuButton.qml")
                    }
                }
                function createBoxes() {

                    var linesArray =  dataPoints.getAnounceList();
                    for (var j = 0; j < linesArray.length; j++) {
                        createBox(linesArray[j])
                    }


                }
                function clearBoxes() {
                    for (var i = 0; i < createdBoxes.length; i++) {
                        createdBoxes[i].destroy() // Oluşturulmuş kutuları yok et
                    }
                    createdBoxes = [] // Diziyi boşalt
                }

            }
            Connections {
            target: dataPoints
                onAnounceFolderUpdated: {
                    grid.clearBoxes();
                    grid.createBoxes();
                    console.log("buradaaayım")
                }
            }
            Component.onCompleted: {
                grid.createBoxes() ;
            }
        }



    }
}
