import QtQuick 2.0
import QtMultimedia
Rectangle {
    width: 160
    height: 90
    color: "black"
    property string sourceVideo
    Video {
        id: video
        anchors.fill: parent
        source: sourceVideo
        fillMode: Video.PreserveAspectFit
        visible: MediaPlayer.ResumedState === mediaPlayer.state
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            video.play();
        }
}
}
