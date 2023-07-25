import QtQuick 2.3
import QtQuick.Window 2.3
import QtQuick.Controls 2.0
Window {
    visible: true
    width: 800
    height: 600
    color: "white"
    Component.onCompleted: {
        x= Qt.application.screens[1].virtualX;
        y= Qt.application.screens[1].virtualY;
    }
    flags: Qt.FramelessWindowHint | Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint



    //Properties
    property int currentDirectionNumber : 0
    property string nextStationName : "Bilinmiyor"
    property string currentStationName :"Bilinmiyor"

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
                onClicked: {
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
            Text{
                anchors.centerIn: parent
                text: "BOZANKAYA"
                font.pixelSize: 24
                elide: Text.ElideRight
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Medium
                font.family: "Verdana"
                color: "white"

            }
            Text {
                id: timeText
                font.pixelSize: 18
                text: Qt.formatTime(new Date(), "hh:mm")
                anchors.right: logoBuyuksehir.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 10
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
                text: new Date().toLocaleDateString(Qt.locale("tr_TR"),"dd MMMM yyyy \ndddd")
                anchors.left: logoUlasim.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 10
                elide: Text.ElideRight
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Medium
                font.family: "Verdana"
                color: "white"
                function set(){
                    dateText.text=new Date().toLocaleDateString(Qt.locale("tr_TR"),"dd MMMM yyyy \ndddd");
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
                text:"GELECEK DURAK : "+ nextStationName
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
                    nextStationText.text = "GELECEK DURAK : "+newStation;
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
    }
    Connections{
        target:dataPoints
        onConfirmStationIDChanged: {
            windowElement.stationID = dataPoints.confirmStationID
            windowElement.stationText = dataPoints.getStationName(windowElement.stationID)
        }
    }
    Connections{
        target:dataPoints
        onCurrentStationChanged:{
            currentStationText.update(dataPoints.getStationName(dataPoints.currentStation))
        }
    }
    Connections{
        target:dataPoints
        onNextStationChanged:{
            nextStationText.update(dataPoints.getStationName(dataPoints.nextStation))
        }
    }
    Connections{
        target:dataPoints
        onCurrentLineChanged:{
            currentDirectionNo.update(dataPoints.currentLine)
        }
    }


}

