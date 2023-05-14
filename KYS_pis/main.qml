
import QtQuick.Window 2.3
import QtQuick 2.3
import QtQuick.Controls 2.15
import QtMultimedia
import QtQml.Models 2.2
import Qt.labs.folderlistmodel 2.4
Window {
    id:root
    visible: true
    width: 1920
    height: 540
    color: "white"
    Component.onCompleted: {
        x= Qt.application.screens[0].virtualX;
        y= Qt.application.screens[0].virtualY;
    }
    flags: Qt.FramelessWindowHint | Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint
    Loader {
        id: secondaryLoader
        source: "Secondary.qml"
        visible: true
        active: true

    }
    Rectangle {
        anchors.left:parent.left
        anchors.top:parent.top
        width: parent.width/2
        height: 540
        color: "transparent"
        Image{
            id:backgroundImageLeftMAin
            anchors.fill: parent
            source:"img/backgroundERciyes.jpg"

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
                text: "İYİ YOLCULUKLAR"
                font.pixelSize: 24
                elide: Text.ElideRight
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Bold
                font.family: "Verdana"
                color: "white"

            }
            Text {
                id: timeText
                font.pixelSize: 24
                text: Qt.formatTime(new Date(), "hh:mm")
                anchors.right: logoBuyuksehir.left
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
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
                font.pixelSize: 18
                text: Qt.formatDate(new Date(), "dd MMMM yyyy \ndddd ")
                anchors.left: logoUlasim.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                elide: Text.ElideRight
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Bold
                font.family: "Verdana"
                color: "white"
                function set(){
                    dateText.text=Qt.formatDate(new Date(), "dd MMMM yyyy \ndddd ");
                }
            }
        }
        Rectangle{
            id:midArea
            anchors.left:parent.left
            anchors.top:topBanner.bottom
            anchors.bottom:botBanner.top
            anchors.right:parent.right
            anchors.margins: 15
            color: "transparent"
            Image{
                id:backgroundImageMidArea
                anchors.fill: parent
                source:"/img/backgroundHalfOpacity.png"
                mipmap:true
            }
            Rectangle{
                id:highlightedArea


            }

        }
        Rectangle{

            id:botBanner
            anchors.left:parent.left
            anchors.bottom:parent.bottom
            width: parent.width
            height: topBanner.height /2
            color: "transparent"
            z:1
            Image{
                id:backgroundImageBotBanner
                anchors.fill: parent
                source:"/img/backgroundHalfOpacity.png"
                mipmap:true
            }
            Image{
                id:logoInstagram
                anchors.right: hastagInstagram.left
                anchors.rightMargin:5
                source:"/img/instaLogo.png"
                height: topBanner.height /2 -5
                fillMode:Image.PreserveAspectFit
                mipmap:true
                z:2
            }
            Text{
                id:hastagInstagram
                anchors.right:logoTwitter.left
                anchors.rightMargin:5
                anchors.verticalCenter: logoInstagram.verticalCenter
                text:"@ulasimkayseri"
                font.pixelSize: 18
                elide: Text.ElideLeft
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Medium
                font.family: "Verdana"
                color: "white"
            }
            Image{
                id:logoTwitter
                anchors.centerIn: parent
                source:"/img/twitterLogo.png"
                height: topBanner.height /2 -5
                fillMode:Image.PreserveAspectFit
                mipmap:true
                z:2
            }
            Text{
                id:hastagTwitter
                anchors.left:logoTwitter.right
                anchors.leftMargin:5
                anchors.verticalCenter: logoTwitter.verticalCenter
                text:"@UlasimKayseri"
                font.pixelSize: 18
                elide: Text.ElideLeft
                antialiasing: true
                font.hintingPreference: Font.PreferNoHinting
                style: Text.Normal
                focus: false
                font.weight: Font.Medium
                font.family: "Verdana"
                color: "white"
            }
            Image{
                id:logoCallCenter
                anchors.left:parent.left
                anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                source:"/img/callcenmterLogo.png"
                height: topBanner.height /2 -5
                fillMode:Image.PreserveAspectFit
                mipmap:true
                z:2
            }



        }

    }
    // Media player area
    Item {
        id:videoArea
        anchors.right:parent.right
        anchors.top:parent.top
        width: parent.width/2
        height: 540

        property int mediaIndex

        FolderListModel {
            id: folderModel
            folder: "file:///C:/Users/ege-t/Desktop/Videolar"
            nameFilters: ["*.mp4"]
        }

        MediaPlayer {
            id: player
            videoOutput: videoutput
            onMediaStatusChanged: {
                if (player.mediaStatus == MediaPlayer.EndOfMedia) {
                    player.source = folderModel.get(videoArea.mediaIndex,"filePath")
                    if(videoArea.mediaIndex < (folderModel.count-1))
                        videoArea.mediaIndex++
                    else
                        videoArea.mediaIndex=0
                }

            }
            onSourceChanged: {
                player.play();
                console.log("onsourcechanged");
            }


        }

        VideoOutput {
            id:videoutput
            anchors.fill: parent
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
           onTriggered: {dateText.set()
           }
       }
    Timer {
        id:videoStarter
        interval:5000
        repeat:false
        running: true
        onTriggered: {
            videoArea.mediaIndex=0
            player.source = folderModel.get(videoArea.mediaIndex,"filePath")
            videoArea.mediaIndex=1
        }
    }

}
