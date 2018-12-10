import QtQuick 2.9
import QtQuick.Controls 2.2
import QtMultimedia 5.9
import Stereo3D 1.0

ApplicationWindow {
    visible: true
    title: qsTr("Line by line")

    MediaPlayer {
        id: leftMediaplayer
        source: "file:///home/pknopf/sample-video.mp4"
        autoPlay: true
    }

    MediaPlayer {
        id: rigthMediaplayer
        source: "file:///home/pknopf/sample-video.mp4"
        autoPlay: true
    }

    Stereo3DVideoOutput {
        leftSource: leftMediaplayer
        rightSource: rigthMediaplayer
        id: threeDMuxer
    }

    VideoOutput {
        anchors.fill: parent
        source: threeDMuxer
    }

    Component.onCompleted: {
        console.log('don2e')
    }
}
