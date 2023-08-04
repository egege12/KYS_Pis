import QtQuick 2.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.0
import QtMultimedia 5.15
Window {
    visible: true
    width: 800
    height: 600
    color: "white"
    Component.onCompleted: {
        x= Qt.application.screens[0].virtualX;
        y= Qt.application.screens[0].virtualY;
    }
    flags: Qt.FramelessWindowHint | Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint



    //Properties
    property int currentDirectionNumber : 0
    property string nextStationName : "Bilinmiyor"
    property string currentStationName :"Bilinmiyor"
    property bool audioPaused : false;
    property int iconSize : 30;
    property int iconPadding: 10;
    //
//    Rectangle {
//        id:testArea
//        anchors.left:parent.left
//        anchors.top:parent.top
//        width: parent.width
//        height: 40
//        color: "white"
//        ButtonBar{
//            id:windowButtonBar
//            anchors.top: parent.top
//            anchors.topMargin:1
//            anchors.right:parent.right
//            anchors.rightMargin:1
//            onFullScreenClicked:{
//                if(fullscreen === true){
//                    root.showNormal()
//                }else{
//                    root.showFullScreen()
//                }
//                fullscreen= !fullscreen}
//            onIconSizeClicked: {
//                if(iconSize === true){
//                    root.showNormal()
//                }else{
//                    root.showMinimized()
//                }
//                iconSize= !iconSize}
//            onEscapeClicked: Qt.quit()

//        }
//    }

    Rectangle {
        anchors.left:parent.left
        anchors.top:parent.top
        width: parent.width
        height: 600
        color: "transparent"
        Image{
            id:backgroundImageLeftMAin
            anchors.fill: parent
            source:"qrc:/img/driverBackground.png"
            mipmap:true
            z:0
        }

        Rectangle{
            id:topBanner
            anchors.left:parent.left
            anchors.top:parent.top
            width: parent.width
            height: parent.height * 0.12
            color: "transparent"
            MouseArea{
                anchors.fill: parent
                onPressAndHold: {
                    Qt.quit()
                }
            }

            Image{
                id:backgroundImageTopBanner
                anchors.fill: parent
                source:"/img/backgroundHalfOpacity.png"
                mipmap:true
            }
            z:1
            Image{
                id:logoUlasim
                anchors.left: parent.left
                anchors.topMargin: 5
                anchors.leftMargin:5
                anchors.top:parent.top
                source:"qrc:/img/kayseriLogo.png"
                height: parent.height - 10
                fillMode: Image.PreserveAspectFit
                mipmap:true
            }
            Image{
                id:logoBuyuksehir
                anchors.right: parent.right
                anchors.topMargin: 5
                anchors.rightMargin:5
                anchors.top:parent.top
                source:"qrc:/img/kayseriBBLogo.png"
                height: parent.height - 10
                fillMode: Image.PreserveAspectFit
                mipmap:true
            }

            Image{
                id:iconConnection
                width:iconSize
                height:iconSize
                anchors.verticalCenter:parent.verticalCenter
                anchors.right: logoBuyuksehir.left
                anchors.rightMargin: 30
                source:"qrc:/img/connection_Lost.png"
                fillMode: Image.PreserveAspectFit
                mipmap:true
                Component.onCompleted: {
                    if(dataPoints.stateNetwork){
                        iconConnection.source="qrc:/img/connection_establish.png"
                    }else{
                        iconConnection.source="qrc:/img/connection_Lost.png"
                    }
                }
            }
            Image{
                id:iconGPS
                width:iconSize
                height:iconSize
                anchors.verticalCenter:parent.verticalCenter
                anchors.right: iconConnection.left
                anchors.rightMargin: iconPadding
                source:"qrc:/img/GPS_nOK.png"
                fillMode: Image.PreserveAspectFit
                mipmap:true
                Component.onCompleted: {
                    if(dataPoints.stateNoGpsInfo){
                        iconGPS.source="qrc:/img/GPS_nOK.png"
                    }else{
                        iconGPS.source="qrc:/img/GPS_OK.png"
                    }
                }
            }
            Image{
                id:iconStation
                width:iconSize
                height:iconSize
                anchors.verticalCenter:parent.verticalCenter
                anchors.right: iconGPS.left
                anchors.rightMargin: iconPadding
                source:"qrc:/img/stationInfo_nok.png"
                fillMode: Image.PreserveAspectFit
                mipmap:true
                Component.onCompleted: {
                    if(dataPoints.stateNoStationInfo){
                        iconStation.source="qrc:/img/stationInfo_nok.png"
                    }else{
                        iconStation.source="qrc:/img/stationInfo_ok.png"
                    }
                }
            }
            Image{
                id:iconappCom
                width:iconSize
                height:iconSize
                anchors.verticalCenter:parent.verticalCenter
                anchors.right: iconStation.left
                anchors.rightMargin: iconPadding
                source:"qrc:/img/comnOk.png"
                fillMode: Image.PreserveAspectFit
                mipmap:true
                Component.onCompleted: {
                    if(dataPoints.comAppOK){
                        iconappCom.source="qrc:/img/comOk.png"
                    }else{
                        iconappCom.source="qrc:/img/comnOk.png"
                    }
                }
            }
            Text {
                id: timeText
                font.pixelSize: 18
                text: Qt.formatTime(new Date(), "hh:mm")
                anchors.left: logoUlasim.right
                anchors.top : parent.top
                anchors.topMargin:12
                anchors.leftMargin: 20
                elide: Text.ElideRight
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Medium
                font.family: "Verdana"
                color: "white"
                function set(){
                    timeText.text=Qt.formatTime(new Date(), "hh:mm");
                }
            }
            Text {
                id: dateText
                font.pixelSize: 18
                text: new Date().toLocaleDateString(Qt.locale("tr_TR"),"dd MMMM yyyy dddd")
                anchors.left: timeText.left
                anchors.top: timeText.bottom
                anchors.topMargin:5
                elide: Text.ElideRight
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Medium
                font.family: "Verdana"
                color: "white"
                function set(){
                    dateText.text=new Date().toLocaleDateString(Qt.locale("tr_TR"),"dd MMMM yyyy dddd");
                }
            }
        }
        Rectangle{
            id:midArea
            anchors.left:parent.left
            anchors.top:topBanner.bottom
            anchors.bottom:botBanner.top
            anchors.right:parent.right
            color: "transparent"
            Image{
                id:backgroundImageMidArea
                anchors.fill: parent
                source:"/img/backgroundHalfOpacity.png"
                mipmap:true
            }
            Frame{
                anchors.fill:parent
                anchors.margins: 1
                z:3
                StackView {
                    id: stack
                    anchors.fill:parent
                    initialItem: "driverMidArea.qml"
                }
            }
        }
        Rectangle{

            id:botBanner
            anchors.left:parent.left
            anchors.bottom:parent.bottom
            width: parent.width
            height: topBanner.height
            color: "transparent"
            z:1
            Image{
                id:backgroundImageBotBanner
                anchors.fill: parent
                source:"/img/backgroundHalfOpacity.png"
                mipmap:true
            }
            Rectangle{
                id: directionnoRectangle
                anchors.left: parent.left
                anchors.bottom:parent.bottom
                anchors.top:parent.top
                width:150
                color:"transparent"
                Text{
                    id:currentDirectionNoHeader
                    anchors.top:parent.top
                    anchors.left:parent.left
                    anchors.topMargin:5
                    anchors.leftMargin:5
                    text:"Aktif Hat:"
                    font.pixelSize: 18
                    elide: Text.ElideLeft
                    antialiasing: true
                    font.hintingPreference: Font.PreferNoHinting
                    style: Text.Normal
                    focus: false
                    font.weight: Font.Bold
                    font.family: "Verdana"
                    color: "white"
                    function update(newNumber){
                        currentDirectionNo.text = newNumber;
                    }
                }
                Text{
                    id:currentDirectionNo
                    anchors.top:currentDirectionNoHeader.bottom
                    anchors.topMargin:15
                    anchors.horizontalCenter: parent.horizontalCenter
                    text:currentDirectionNumber
                    font.pixelSize: 18
                    elide: Text.ElideLeft
                    antialiasing: true
                    font.hintingPreference: Font.PreferNoHinting
                    style: Text.Normal
                    focus: false
                    font.weight: Font.Bold
                    font.family: "Verdana"
                    color: "white"
                    function update(newNumber){
                        currentDirectionNo.text = newNumber;
                    }
                }
            }


            Text{
                id:currentStationText
                anchors.left:directionnoRectangle.right
                anchors.leftMargin:10
                anchors.top:parent.top
                anchors.topMargin:10
                text:"ŞİMDİKİ DURAK : "+ currentStationName
                font.pixelSize: 18
                elide: Text.ElideLeft
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Bold
                font.family: "Verdana"
                color: "white"
                function update(newStation){
                    currentStationText.text = "ŞİMDİKİ DURAK : "+newStation;
                }
            }
            Text{
                id:nextStationText
                anchors.left:directionnoRectangle.right
                anchors.leftMargin:10
                anchors.top:currentStationText.bottom
                anchors.topMargin:10
                text:"SONRAKİ DURAK : "+ nextStationName
                font.pixelSize: 18
                elide: Text.ElideLeft
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Bold
                font.family: "Verdana"
                color: "white"
                function update(newStation){
                    nextStationText.text = "SONRAKİ DURAK : "+newStation;
                }
            }


        }
    }
    Timer {
        id: timeTimer
        interval: 1000
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: timeText.set()
    }
    Timer {
        id: dateTimer
        interval: 3600
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: dateText.set()
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
    Connections{
        target:dataPoints
        onConfirmPopup: {
            if(!popupWindow.opened){
                console.log("onConfirmPopup çağırıldı ");
                popupWindow.open();
            }
            windowElement.textMessage = "Yukarıdaki istasyondan mı başlıyorsunuz?"
            windowElement.stationID = dataPoints.confirmStationID
            windowElement.stationText = dataPoints.getStationName(windowElement.stationID)
        }
        onConfirmStationIDChanged: {
            windowElement.stationID = dataPoints.confirmStationID
            windowElement.stationText = dataPoints.getStationName(windowElement.stationID)
        }
        onStateNetworkChanged:{
            if(dataPoints.stateNetwork){
                iconConnection.source="qrc:/img/connection_establish.png"
            }else{
                iconConnection.source="qrc:/img/connection_Lost.png"
            }
        }
        onStateNoGpsInfoChanged:{
            if(dataPoints.stateNoGpsInfo){
                iconGPS.source="qrc:/img/GPS_nOK.png"
            }else{
                iconGPS.source="qrc:/img/GPS_OK.png"
            }
        }
        onStateNoStationInfoChanged:{
            if(dataPoints.stateNoStationInfo){
                iconStation.source="qrc:/img/stationInfo_nok.png"
            }else{
                iconStation.source="qrc:/img/stationInfo_ok.png"
            }
        }
        onCurrentStationChanged:{
            currentStationText.update(dataPoints.getStationName(dataPoints.currentStation))
        }
        onNextStationChanged:{
            nextStationText.update(dataPoints.getStationName(dataPoints.nextStation))
        }
        onCurrentLineChanged:{
            currentDirectionNo.update(dataPoints.currentLine)
        }
        onComAppOKChanged:{
            if(dataPoints.comAppOK){
                iconappCom.source="qrc:/img/comOk.png"
            }else{
                iconappCom.source="qrc:/img/comnOk.png"
            }
        }
    }



    MediaPlayer {
        id: playerSound
        onStatusChanged: {
            switch (playerSound.status) {
                case MediaPlayer.NoMedia:
                    //console.log("NoMedia");
                    break;
                case MediaPlayer.Loading:
                    //console.log("Loading");
                    break;
                case MediaPlayer.Loaded:
                    //console.log("Loaded");
                    break;
                case MediaPlayer.Buffering:
                    //console.log("Buffering");
                    break;
                case MediaPlayer.Stalled:
                    //console.log("Stalled");
                    break;
                case MediaPlayer.Buffered:
                    //console.log("Buffered");
                    break;
                case MediaPlayer.EndOfMedia:
                    playerSound.source="";
                    dataPoints.playSound="";
                    audioPaused=false;
                    break;
                case MediaPlayer.InvalidMedia:
                    //console.log("InvalidMedia");
                    break;
                case MediaPlayer.UnknownStatus:
                    //console.log("UnknownStatus");
                    break;
            }
        }
        onSourceChanged: {
            if(!audioPaused){
                if(playerSound.source !==""){
                    playerSound.play();
                    dataPoints.logMediaPlay(playerSound.source)
                }
            }
        }

    }
    Audio{
        id:audio
        source:playerSound
    }
    MediaPlayer {
        id: playerStations
        onStatusChanged: {
            switch (playerStations.status) {
                case MediaPlayer.NoMedia:
                    //console.log("NoMedia");
                    break;
                case MediaPlayer.Loading:
                    //console.log("Loading");
                    break;
                case MediaPlayer.Loaded:
                    //console.log("Loaded");
                    break;
                case MediaPlayer.Buffering:
                    //console.log("Buffering");
                    break;
                case MediaPlayer.Stalled:
                    //console.log("Stalled");
                    break;
                case MediaPlayer.Buffered:
                    //console.log("Buffered");
                    break;
                case MediaPlayer.EndOfMedia:
                    playerStations.source="";
                    dataPoints.pauseAnounce = false;
                    break;
                case MediaPlayer.InvalidMedia:
                    //console.log("InvalidMedia");
                    break;
                case MediaPlayer.UnknownStatus:
                    //console.log("UnknownStatus");
                    break;
            }
        }
        onSourceChanged: {
                if(playerStations.source !==""){
                    dataPoints.pauseAnounce = true;
                    playerStations.play();
                }else{
                    dataPoints.pauseAnounce = false;
                }



        }

    }
    Audio{
        id:audioStations
        source:playerStations
    }

    Connections{
        target:dataPoints
        onPlaySoundStationsChanged:
            if(playerStations.source != dataPoints.playSoundStations) {
                playerStations.source = dataPoints.playSoundStations;
            }else{
                playerStations.source = "";
            }
    }
    Connections{
        target:dataPoints
        onPlaySoundChanged:
            if(playerSound.source != dataPoints.playSound) {
                playerSound.source = dataPoints.playSound;
            }else{
                playerSound.source = "";
            }
    }
    Connections{
        target:dataPoints
        onPauseAnounceChanged:{
            if(!dataPoints.pauseAnounce){
                playerSound.play();
                audioPaused=false;
            }else{
                playerSound.pause();
                audioPaused=true;
            }
        }
    }
}

