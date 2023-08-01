import QtQuick.Window 2.3
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia 5.15
import QtQml.Models 2.2
import Qt.labs.folderlistmodel 2.15

Window {
    id:root
    visible: true
    width: 1920
    height: 540
    color: "white"
    Component.onCompleted: {
        x= Qt.application.screens[1].virtualX;
        y= Qt.application.screens[1].virtualY;

        if(dataPoints.stateDispTextOnStationArea){
            rightSide.visible=false;
            rightSideScreenSaver.visible=true;
            console.log(rightSide.width+" "+rightSide.height);
        }else{
            rightSide.visible=true;
            rightSideScreenSaver.visible=false;
            console.log("visible true");
        }
    }
    flags: Qt.FramelessWindowHint | Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint
    Loader {
        id: secondaryLoader
        source: "Secondary.qml"
        visible: true
        active: true

    }
    Rectangle {

        id:infoArea
        anchors.left:parent.left
        anchors.top:parent.top
        width: (parent.width-blackArea.width)/2
        height: parent.height
        color: "transparent"
        Image{
            id:backgroundImageLeftMAin
            anchors.fill: parent
            source:"qrc:/img/Mainbackground.png"

            mipmap:true
            z:0
        }


        Rectangle{
            id:leftSide
            anchors.left:parent.left
            anchors.top:parent.top
            width: 293
            height: parent.height
            color: "transparent"
            Text {
                id: timeText
                font.pixelSize: 72
                text: Qt.formatTime(new Date(), "hh:mm")
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.top:parent.top
                anchors.topMargin: 40
                width:timeText.implicitWidth
                height:timeText.implicitHeight
                elide: Text.ElideRight
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Bold
                font.family: "Verdana"
                color: "white"
                function set(){
                    timeText.text=Qt.formatTime(new Date(), "hh:mm");
                }
            }
            Text {
                id: dateText
                font.pixelSize: 24
                text: new Date().toLocaleDateString(Qt.locale("tr_TR"),"dd MMMM yyyy \n        dddd")
                anchors.top: timeText.bottom
                anchors.topMargin: 50
                anchors.horizontalCenter: parent.horizontalCenter
                width:timeText.implicitWidth
                height:timeText.implicitHeight
                elide: Text.ElideRight
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Bold
                font.family: "Verdana"
                color: "white"
                function set(){
                    dateText.text= new Date().toLocaleDateString(Qt.locale("tr_TR"),"dd MMMM yyyy \n        dddd");
                }
            }
            z:1
            Rectangle{
                id:banners
                anchors.left:parent.left
                anchors.right: parent.right
                anchors.leftMargin:30
                anchors.rightMargin:30
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                /*Testing reasons*/
                //Text{
                //    id:longitude
                //    font.pixelSize: 18
                //    text: "Boylam"
                //    anchors.bottom: logoUlasim.top
                //    anchors.bottomMargin: 50
                //    anchors.left:logoUlasim.left
                //    elide: Text.ElideRight
                //    antialiasing: true
                //    font.hintingPreference: Font.PreferNoHinting
                //    style: Text.Normal
                //    focus: false
                //    font.weight: Font.Bold
                //    font.family: "Verdana"
                //    color: "white"
                //}
                //Text{
                //    id:latidude
                //    font.pixelSize: 18
                //    text: "Enlem"
                //    anchors.bottom: longitude.top
                //    anchors.bottomMargin: 50
                //    anchors.left:longitude.left
                //    elide: Text.ElideRight
                //    antialiasing: true
                //    font.hintingPreference: Font.PreferNoHinting
                //    style: Text.Normal
                //    focus: false
                //    font.weight: Font.Bold
                //    font.family: "Verdana"
                //    color: "white"
                //}

                Image{
                    id:logoUlasim
                    anchors.left: parent.left
                    anchors.right: seperatorBanners.left
                    anchors.verticalCenter: parent.verticalCenter
                    source:"qrc:/img/kayseriLogo.png"
                    width:100
                    fillMode: Image.PreserveAspectFit
                    mipmap:true
                }
                Rectangle{
                    id:seperatorBanners
                    anchors.left: logoUlasim.right
                    anchors.top:parent.top
                    anchors.bottom:parent.bottom
                    width:30
                    color:"white"
                }

                Image{
                    id:logoAlo
                    anchors.left: seperatorBanners.right
                    anchors.leftMargin:5
                    anchors.right:parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    source:"qrc:/img/callcenmterLogo.png"
                    fillMode: Image.PreserveAspectFit
                    mipmap:true
                }
                Image{
                    id:iconSpeed
                    anchors.top: logoUlasim.bottom
                    anchors.topMargin:30
                    anchors.left:logoUlasim.left
                    width:60
                    source:"qrc:/img/iconSpeed.png"
                    fillMode: Image.PreserveAspectFit
                    mipmap:true
                }
                Text {
                    id: speedText
                    font.pixelSize: 52
                    text: ""
                    anchors.bottom: iconSpeed.bottom
                    anchors.bottomMargin: -10
                    anchors.left : iconSpeed.right
                    anchors.leftMargin: 30
                    elide: Text.ElideRight
                    antialiasing: true
                    font.hintingPreference: Font.PreferNoHinting
                    style: Text.Normal
                    focus: true
                    font.weight: Font.Bold
                    font.family: "Tahoma"
                    color: "white"
                    function set(){
                        speedText.text= dataPoints.vehicleSpeed
                    }
                    Component.onCompleted: {
                        speedText.set();
                    }
                }
                Text {
                    id: speedkmhText
                    font.pixelSize: 24
                    text: "km\h"
                    anchors.bottom: speedText.bottom
                    anchors.bottomMargin: 5
                    anchors.right : logoAlo.right
                    elide: Text.ElideRight
                    antialiasing: true
                    font.hintingPreference: Font.PreferNoHinting
                    style: Text.Normal
                    focus: true
                    font.weight: Font.Bold
                    font.family: "Tahoma"
                    color: "white"
                }
            }




        }
        Rectangle{
            id:rightSideScreenSaver
            anchors.left: leftSide.right
            anchors.right:parent.right
            anchors.top:parent.top
            anchors.bottom:parent.bottom
            color:"transparent"
            Image{
                id:imageScreenSaver
                anchors.fill: parent
                antialiasing: true
                source: "qrc:/img/logoScreenSaver_kys.png"
                opacity: 1.0
                fillMode:Image.PreserveAspectFit
            }
        }

        Rectangle{
            id:rightSide
            anchors.left: leftSide.right
            anchors.right:parent.right
            anchors.top:parent.top
            anchors.bottom:parent.bottom
            color:"transparent"


            Rectangle{
                     id:highlightedArea
                     anchors.left: parent.left
                     anchors.leftMargin:143
                     anchors.top:parent.top
                     anchors.topMargin:42
                     anchors.bottom:parent.bottom
                     width:parent.width * .6
                     color:"transparent"


                     ListModel{
                         id: duraklar

                         ListElement{
                             name:""
                         }
                         ListElement{
                             name:""
                         }
                         ListElement{
                             name:""
                         }
                         ListElement{
                             name:""
                         }

                     }

                     ListView{
                         id:myListview
                         anchors.fill: parent
                         property bool colorcontrol :true;
                         model: duraklar
                         focus:true
                         spacing:48
                         delegate:
                             Rectangle{
                                 id:delegateRect
                                 width:highlightedArea.width
                                 height:highlightedArea.height / 6
                                 color:"transparent"

                                 Text {
                                             id:text
                                             text: name
                                             font.capitalization: Font.AllUppercase
                                             anchors.fill: parent
                                             elide: Text.ElideNone
                                             antialiasing: true
                                             font.hintingPreference: Font.PreferNoHinting
                                             verticalAlignment: Text.AlignTop
                                             style: Text.Normal
                                             font.weight: Font.Bold
                                             wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                                             maximumLineCount: 2
                                             font.pixelSize: Math.min(32, ((parent.width / name.length) * 2.5))
                                             font.family: "Verdana"
                                             color: ((duraklar).get((duraklar.count/duraklar.count)-1).name === name) ? ("cyan") : ("black")
                                         }


                             }


                         populate: Transition{
                             NumberAnimation{
                                 properties:"x,y";
                                 duration:300
                             }
                         }
                         add: Transition{

                             NumberAnimation {
                                 property:"x";
                                 from:1500;
                                 to: 0;
                                 duration:1000
                             }
                             NumberAnimation {
                                 property:"opacity";
                                 from:0;
                                 to: 1.0;
                                 duration:1000
                             }



                         }

                         remove: Transition{

                             NumberAnimation {
                                 property:"x";
                                 from:0;
                                 to: -1500;
                                 duration:1000
                             }
                             NumberAnimation {
                                 property:"opacity";
                                 from:1.0;
                                 to: 0;
                                 duration:1000
                             }


                         }
                     }
                 }
        }

    }
    Rectangle{
        id:blackArea
        height:parent.height
        width: 30
        anchors.left: infoArea.right
        color:"black"
    }

    // Media player area
    Rectangle {
        id:videoArea
        anchors.right:parent.right
        anchors.top:parent.top
        width: (parent.width-blackArea.width)/2
        height: parent.height
        color : "black"
        property int mediaIndex
        property bool mediawait : false;
        Image {
            id: screenSaverRight
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            source:"qrc:/img/nicetrip_1.png"
            fillMode: Image.PreserveAspectFit
            visible:false
            z:3
        }
        FolderListModel {
            id: folderModel
            folder: "file:///C:/appKYS_Pis/PISVideos"
            nameFilters: ["*.mp4"]
        }
        property int endOfMediaCounter : 0;
        MediaPlayer {
            id: player
            muted: true
            onStatusChanged: {
                if (player.status == MediaPlayer.EndOfMedia) {

                    if(folderModel.count == 1)
                        player.play();
                    else if(videoArea.mediaIndex < (folderModel.count-1)){
                        videoArea.mediaIndex++
                    }else{
                        videoArea.mediaIndex=0
                    }
                    player.source = folderModel.get(videoArea.mediaIndex,"filePath")

                }else if(player.mediaStatus === MediaPlayer.InvalidMedia || player.mediaStatus === MediaPlayer.NoMedia ){
                    videoArea.mediaIndex=0
                }
            }

            function check(){
                if((player.status === MediaPlayer.NoMedia) || (player.status ===MediaPlayer.InvalidMedia) ||(videoArea.endOfMediaCounter>2)||(player.error !== MediaPlayer.NoError)|| (player.status ===MediaPlayer.UnknownStatus) || (player.status ===MediaPlayer.Stalled)){
                    dataPoints.setVideoUnavailable();
                    if(!videoArea.mediawait){
                        videoArea.mediawait = true
                        videoStarter.start()
                    }
                }else{
                    dataPoints.setVideoAvailable();
                }
                switch (player.status) {
                    case MediaPlayer.NoMedia:
                        console.log("NoMedia");
                        //dataPoints.errCode="Medya yok"
                        videoArea.endOfMediaCounter=0;
                        break;
                    case MediaPlayer.Loading:
                        console.log("Loading");
                        //dataPoints.errCode="yükleniyor."
                        videoArea.endOfMediaCounter=0;
                        break;
                    case MediaPlayer.Loaded:
                        console.log("Loaded");
                        //dataPoints.errCode="yüklendi."
                        videoArea.endOfMediaCounter=0;
                        break;
                    case MediaPlayer.Buffering:
                        console.log("Buffering");
                        dataPoints.setVideoAvailable();
                        //dataPoints.errCode="Stoklanıyor"
                        videoArea.endOfMediaCounter=0;
                        break;
                    case MediaPlayer.Stalled:
                        console.log("Stalled");
                        //dataPoints.errCode="Video çöktü"
                        break;
                    case MediaPlayer.Buffered:
                        console.log("Buffered");
                        dataPoints.setVideoAvailable();
                        //dataPoints.errCode="Buffer yapıldı"
                        videoArea.endOfMediaCounter=0;
                        break;
                    case MediaPlayer.EndOfMedia:
                        console.log("EndOfMedia");
                        //dataPoints.errCode="Medya sonu"
                        videoArea.endOfMediaCounter= 1+videoArea.endOfMediaCounter
                        break;
                    case MediaPlayer.InvalidMedia:
                        console.log("InvalidMedia");
                        //dataPoints.errCode="Geçersiz Medya"
                        break;
                    case MediaPlayer.UnknownStatus:
                        //dataPoints.errCode="Bilinmeyen durum"
                        console.log("UnknownStatus");
                        break;
                }
            }


            onSourceChanged: {
                if(player.source == ""){
                    console.log("boş video yolu")
                }else{
                    dataPoints.logVideoPlay(folderModel.get(videoArea.mediaIndex,"fileName"));
                    player.play();
                }



            }


        }

        VideoOutput {
               anchors.fill: parent
               source: player
               fillMode: VideoOutput.PreserveAspectCrop
           }
    }

    Timer {
        id: timeTimer
        interval: 1000
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            timeText.set()
        }
    }
    Timer {
        id: nextstationTimer
        interval: 2000
        repeat: false
        running: true
        onTriggered: {
            if(nextStationTag){
                dataPoints.playSoundStations="file:///"+dataPoints.getPathAudio(dataPoints.currentStation);
                nextStationTag=false;
            }
        }
    }
    Timer {
        id: dateTimer
        interval: 3600
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            dateText.set();
            player.check();
        }
    }
    Timer {
        id:videoStarter
        interval:2000
        repeat:false
        running: true
        onTriggered: {
            videoArea.mediaIndex=0
            player.source = folderModel.get(videoArea.mediaIndex,"filePath")
            videoArea.mediawait = false
        }
    }

    property bool nextStationTag : false;

    Connections{
        target: dataPoints
        onAnounceNextStation:{
            dataPoints.playSoundStations="file:///C:/appKYS_Pis/PISStations/next_station.mp3"
            nextstationTimer.start();
            nextStationTag=true;
        }
        onAnounceCurrentStation:{
           dataPoints.playSoundStations="file:///"+dataPoints.getPathAudio(dataPoints.currentStation);
        }
        onVehicleSpeedChanged:{
            if(dataPoints.vehicleSpeed > 200){
                speedText.text = ""
                speedText.visible = false
                iconSpeed.visible=false
                speedkmhText.visible =false
            }else{
                 speedText.text = dataPoints.vehicleSpeed
                 speedText.visible = true
                 iconSpeed.visible=true
                 speedkmhText.visible =true
            }
        }
        onStateDispWatchOnVideoAreaChanged:{
           screenSaverRight.visible= dataPoints.stateDispWatchOnVideoArea;
        }
        onLoadViewFour:{
            duraklar.clear();
            for (var i = 0; i < 4; i++) {
                        duraklar.append({"name": dataPoints.getViewFourMember(i)});
            }
        }
        onUpdateViewFour:{
            duraklar.remove(0,1);
            duraklar.append({"name": dataPoints.getViewFourMember(3)});
            delegateRect.update();
        }
        onStateDispTextOnStationAreaChanged:{
            if(dataPoints.stateDispTextOnStationArea){
                rightSide.visible=false;
                rightSideScreenSaver.visible=true;
                console.log(rightSide.width+" "+rightSide.height);
            }else{
                rightSide.visible=true;
                rightSideScreenSaver.visible=false;
                console.log("visible true");
            }
        }
        onVideoFolderUpdated:{
           player.play();
        }
        /*Testing reason*/
        //onActualLongitudeChanged:{
        //    longitude.text="Boylam: "+dataPoints.actualLongitude;
        //}
        //onActualLatitudeChanged:{
        //    latidude.text="//: "+dataPoints.actual//tude;
        //}

    }


}
