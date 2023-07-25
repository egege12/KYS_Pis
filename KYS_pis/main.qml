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
                             name:"Durak1"
                         }
                         ListElement{
                             name:"Durak2"
                         }
                         ListElement{
                             name:"Durak3"
                         }
                         ListElement{
                             name:"Durak4"
                         }

                     }

                     ListView{
                         id:myListview
                         anchors.fill: parent

                         model: duraklar
                         focus:true
                         spacing:48
                         delegate:
                             Rectangle{
                                 width:highlightedArea.width
                                 height:highlightedArea.height / 6
                                 color:"transparent"

                                 Text {
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
                                             color: (duraklar.get(0).name === name) ? ((root.pulse === true) ? "gray" : "cyan") : (duraklar.get(0).name === name) ? "gray" : "black"
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
            onStatusChanged: {
                if(videoArea.mediaIndex > (folderModel.count-1))
                    videoArea.mediaIndex=0
            }
            function update(){
                folderModel.folder = "";
                folderModel.reload();
            }
            function reload(){
                folderModel.folder = "file:///C:/appKYS_Pis/PISVideos";
                videoStarter.start();
            }
        }

        MediaPlayer {
            id: player
            muted: true
            onStatusChanged: {
                if (player.status == MediaPlayer.EndOfMedia) {
                    dataPoints.setVideoAvailable();
                    player.source = folderModel.get(videoArea.mediaIndex,"filePath")
                    if(videoArea.mediaIndex < (folderModel.count-1))
                        videoArea.mediaIndex++
                    else
                        videoArea.mediaIndex=0
                }else if(player.mediaStatus === MediaPlayer.InvalidMedia || player.mediaStatus === MediaPlayer.NoMedia ){
                    videoArea.mediaIndex=0
                }

            }
            function check(){
                if(player.status === MediaPlayer.NoMedia){
                    dataPoints.setVideoUnavailable();
                    folderModel.update();
                }else{
                    dataPoints.setVideoAvailable();
                }
                switch (player.status) {
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
                        //console.log("EndOfMedia");
                        break;
                    case MediaPlayer.InvalidMedia:
                        //console.log("InvalidMedia");
                        break;
                    case MediaPlayer.UnknownStatus:
                        //console.log("UnknownStatus");
                        break;
                }
            }

            onPlaying: {
                dataPoints.logVideoPlay(folderModel.get(videoArea.mediaIndex,"fileName"));
            }

            onSourceChanged: {
                player.play();

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
        onTriggered: {timeText.set()
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
            videoArea.mediaIndex=1
        }
    }


    property bool soundEnd: false;
    MediaPlayer {
        id: playerSound
        autoLoad:false
        onStatusChanged: {
            if (player.status == MediaPlayer.EndOfMedia) {
                playerSound.source="";
                root.soundEnd = true;
            }
        }
        onSourceChanged: {
            console.log(playerSound.source)
            if(root.soundEnd == true){
                root.soundEnd = false;
            }else{
               playerSound.play();
            }
        }

    }
    Connections{
        target: dataPoints
        onAnounceNextStation:{
            playerSound.source = "file:///"+dataPoints.getPathAudio(dataPoints.nextStation)
            console.log("sıradaki istasyon")
        }
    }
    Connections{
        target: dataPoints
        onAnounceCurrentStation:{
           playerSound.source = "file:///"+dataPoints.getPathAudio(dataPoints.currentStation)
            console.log("şimdiki istasyon")
        }
    }
    Connections{
        target: dataPoints
        onVideoFolderUpdated:{
           playerSound.play();
        }
    }
    Connections{
        target: dataPoints
        onStateDispWatchOnVideoAreaChanged:{
           screenSaverRight.visible= dataPoints.stateDispWatchOnVideoArea;
        }
    }
    Connections{
        target: dataPoints
        onLoadViewFour:{
            duraklar.clear();
            for (var i = 0; i < 4; i++) {
                        duraklar.append({"name": dataPoints.getViewFourMember(i)});
            }
        }
    }
    Connections{
        target: dataPoints
        onUpdateViewFour:{
            duraklar.remove(0,1);
            duraklar.append({"name": dataPoints.getViewFourMember(3)});

        }
    }



}
