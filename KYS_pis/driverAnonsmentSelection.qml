import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia
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
        //ANONS1
        Item{
            id:anunc1
            anchors.left:buttonBack.right
            anchors.leftMargin:10
            anchors.top:parent.top
            width : (parent.width - buttonBack.width)/2
            height: parent.height/ 4
            Image{
                id:backgroundImageAn1
                anchors.fill: parent
                source:"/img/backgroundHalfOpacity.png"
                mipmap:true
            }
            Text{
                id:priortyAnoncement
                anchors.left:parent.left
                anchors.top:parent.top
                text:"Anons 1: Öncelikli iniş ve binişler"
                font.pixelSize: 18
                elide: Text.ElideLeft
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Bold
                font.family: "Verdana"
                color: "white"

            }
            Switch {
                id: switchAnounce1
                text: (rectangleAnonuncement.announcement_priorty == true) ? ("AKTIF"):("PASIF")
                anchors.left:parent.left
                anchors.leftMargin:5
                anchors.verticalCenter: parent.verticalCenter
                visible: true
                indicator: Rectangle {
                    implicitWidth: 48
                    implicitHeight: 26
                    x: switchAnounce1.leftPadding
                    y: parent.height / 2 - height / 2
                    radius: 13
                    color: switchAnounce1.checked ? "#032896" : "#ffffff"
                    border.color: switchAnounce1.checked ? "#032896" : "#cccccc"

                    Rectangle {
                        x: switchAnounce1.checked ? parent.width - width : 0
                        width: 26
                        height: 26
                        radius: 13
                        color: switchAnounce1.down ? "#cccccc" : "#ffffff"
                        border.color: switchAnounce1.checked ? "#032896" : "#999999"
                    }
                }

                contentItem: Text {
                    text: switchAnounce1.text
                    font: switchAnounce1.font
                    opacity: enabled ? 1.0 : 0.3
                    color: "white"
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: switchAnounce1.indicator.width + switchAnounce1.spacing
                    style: Text.Normal
                }
                onCheckedChanged: {
                    rectangleAnonuncement.announcement_priorty = switchAnounce1.checked
                }

            }
            MenuButton {
                id : buttonAnounce1
                anchors.right:parent.right
                anchors.left: switchAnounce1.right
                anchors.verticalCenter: parent.verticalCenter
                height: 50
                buttonImageSource : "qrc:/img/anonunceIcon.png"
                radius: 1
                imageRatio: 0.7
                disableButtonClick: false
                buttonText: ""
                onButtonClicked:{
                    playerSound.source="file:///C:/Users/ege-t/Desktop/anonslar/priority.mp3"

                }
            }
        }
        //ANONS2
        Item{
                    id:anunc2
                    anchors.left:buttonBack.right
                    anchors.leftMargin:10
                    anchors.top:anunc1.bottom
                    width : (parent.width - buttonBack.width)/2
                    height: parent.height/ 4
                    Image{
                        id:backgroundImageAn2
                        anchors.fill: parent
                        source:"/img/backgroundHalfOpacity.png"
                        mipmap:true
                    }
                    Text{
                        id:nextstationAnoncement
                        anchors.left:parent.left
                        anchors.top:parent.top
                        text:"Anons 2: Gelecek durak anonsları"
                        font.pixelSize: 18
                        elide: Text.ElideLeft
                        antialiasing: true
                        font.hintingPreference: Font.PreferNoHinting
                        style: Text.Normal
                        focus: false
                        font.weight: Font.Bold
                        font.family: "Verdana"
                        color: "white"

                    }
                    Switch {
                        id: switchAnounce2
                        text: (rectangleAnonuncement.anouncement_next_station == true) ? ("AKTIF"):("PASIF")
                        anchors.left:parent.left
                        anchors.leftMargin:5
                        anchors.verticalCenter: parent.verticalCenter
                        visible: true
                        indicator: Rectangle {
                            implicitWidth: 48
                            implicitHeight: 26
                            x: switchAnounce2.leftPadding
                            y: parent.height / 2 - height / 2
                            radius: 13
                            color: switchAnounce2.checked ? "#032896" : "#ffffff"
                            border.color: switchAnounce2.checked ? "#032896" : "#cccccc"

                            Rectangle {
                                x: switchAnounce2.checked ? parent.width - width : 0
                                width: 26
                                height: 26
                                radius: 13
                                color: switchAnounce2.down ? "#cccccc" : "#ffffff"
                                border.color: switchAnounce2.checked ? "#032896" : "#999999"
                            }
                        }

                        contentItem: Text {
                            text: switchAnounce2.text
                            font: switchAnounce2.font
                            opacity: enabled ? 1.0 : 0.3
                            color: "white"
                            verticalAlignment: Text.AlignVCenter
                            leftPadding: switchAnounce2.indicator.width + switchAnounce2.spacing
                            style: Text.Normal
                        }
                        onCheckedChanged: {
                            rectangleAnonuncement.anouncement_next_station = switchAnounce2.checked
                        }

                    }
                    MenuButton {
                        id : buttonAnounce2
                        anchors.right:parent.right
                        anchors.left: switchAnounce2.right
                        anchors.verticalCenter: parent.verticalCenter
                        height: 50
                        buttonImageSource : "qrc:/img/anonunceIcon.png"
                        radius: 1
                        imageRatio: 0.7
                        disableButtonClick: false
                        buttonText: ""
                        onButtonClicked:{
                            //burada next station anonusunu başlatacağız
                        }
                    }
                }
        //ANONS3
        Item{
                            id:anunc3
                            anchors.left:buttonBack.right
                            anchors.leftMargin:10
                            anchors.top:anunc2.bottom
                            width : (parent.width - buttonBack.width)/2
                            height: parent.height/ 4
                            Image{
                                id:backgroundImageAn3
                                anchors.fill: parent
                                source:"/img/backgroundHalfOpacity.png"
                                mipmap:true
                            }
                            Text{
                                id:currenttstationAnoncement
                                anchors.left:parent.left
                                anchors.top:parent.top
                                text:"Anons 3: Şimdiki durak anonsları"
                                font.pixelSize: 18
                                elide: Text.ElideLeft
                                antialiasing: true
                                font.hintingPreference: Font.PreferNoHinting
                                style: Text.Normal
                                focus: false
                                font.weight: Font.Bold
                                font.family: "Verdana"
                                color: "white"

                            }
                            Switch {
                                id: switchAnounce3
                                text: (rectangleAnonuncement.anouncement_current_station == true) ? ("AKTIF"):("PASIF")
                                anchors.left:parent.left
                                anchors.leftMargin:5
                                anchors.verticalCenter: parent.verticalCenter
                                visible: true
                                indicator: Rectangle {
                                    implicitWidth: 48
                                    implicitHeight: 26
                                    x: switchAnounce3.leftPadding
                                    y: parent.height / 2 - height / 2
                                    radius: 13
                                    color: switchAnounce3.checked ? "#032896" : "#ffffff"
                                    border.color: switchAnounce3.checked ? "#032896" : "#cccccc"

                                    Rectangle {
                                        x: switchAnounce3.checked ? parent.width - width : 0
                                        width: 26
                                        height: 26
                                        radius: 13
                                        color: switchAnounce3.down ? "#cccccc" : "#ffffff"
                                        border.color: switchAnounce3.checked ? "#032896" : "#999999"
                                    }
                                }

                                contentItem: Text {
                                    text: switchAnounce3.text
                                    font: switchAnounce3.font
                                    opacity: enabled ? 1.0 : 0.3
                                    color: "white"
                                    verticalAlignment: Text.AlignVCenter
                                    leftPadding: switchAnounce3.indicator.width + switchAnounce3.spacing
                                    style: Text.Normal
                                }
                                onCheckedChanged: {
                                    rectangleAnonuncement.anouncement_current_station = switchAnounce3.checked
                                }

                            }
                            MenuButton {
                                id : buttonAnounce3
                                anchors.right:parent.right
                                anchors.left: switchAnounce3.right
                                anchors.verticalCenter: parent.verticalCenter
                                height: 50
                                buttonImageSource : "qrc:/img/anonunceIcon.png"
                                radius: 1
                                imageRatio: 0.7
                                disableButtonClick: false
                                buttonText: ""
                                onButtonClicked:{
                                    //burada next station anonusunu başlatacağız
                                }
                            }
                        }
    }
    MediaPlayer {
        id: playerSound
        audioOutput: audio
        onMediaStatusChanged: {
            if (playerSound.mediaStatus == MediaPlayer.EndOfMedia) {
                playerSound.source = ""
            }
        }
        onSourceChanged: {
            playerSound.play();
        }

    }
    AudioOutput{
        id:audio
    }


}
