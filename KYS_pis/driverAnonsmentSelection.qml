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
        Rectangle{
            id:configurationArea
            height: 50
            anchors.bottom:parent.bottom
            anchors.right:parent.right
            anchors.left:buttonBack.right
            anchors.leftMargin:5
            color:"transparent"
            border.color: "gray"
            border.width: 1
            Text{
                anchors.left:parent.left
                anchors.leftMargin:15
                anchors.verticalCenter: parent.verticalCenter
                text: "Otomatik anonslar seçili sürede bir sırasıyla oynatılır."
                font.pixelSize: 14
                elide: Text.ElideRight
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Medium
                font.family: "Verdana"
                color: "white"
            }
            ComboBox{
                id:anounceCycleComboBox
                width: 200
                height: 30
                editable:false
                anchors.right:parent.right
                anchors.rightMargin:15
                anchors.verticalCenter: parent.verticalCenter
                displayText: dataPoints.periodOfAnounce
                visible: true
                model:
                    [   "30 Dakika" ,
                        "45 Dakika" ,
                        "1 Saat"    ,
                        "2 Saat"    ,
                        "3 Saat"    ,
                        "Günde 1"   ,]
                onActivated: {
                    dataPoints.periodOfAnounce = currentText;
                    displayText=currentText;
                }
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
            anchors.bottom: configurationArea.top
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

                        var textItem = Qt.createQmlObject(
                           "import QtQuick 2.15; Text { text: '" + text + "'; color: 'white'; style: Text.Normal; focus: false; font.weight: Font.Bold; font.family: 'Verdana'; font.pixelSize: 12}",
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
                        switchItem.checked = false;
                    } else {
                        console.log("Error loading MenuButton.qml")
                    }
                }
                function createBoxes() {

                    var linesArray =  dataPoints.getAnounceList("C:/appKYS_Pis/PISSpecialAnounce")
                    for (var j = 0; j < linesArray.length; j++) {
                        createBox(linesArray[j])
                    }


                }
                Component.onCompleted: createBoxes()
            }
        }



    }
}
