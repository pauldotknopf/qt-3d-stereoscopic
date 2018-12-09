import QtQuick 2.9
import QtQuick.Controls 2.2
import QtMultimedia 5.9
import Stereo3D 1.0

ApplicationWindow {
    visible: true
    title: qsTr("Line by line")

    MediaPlayer {
        id: mediaplayer
        source: "file:///home/pknopf/sample-video.mp4"
        autoPlay: true
    }

    VideoOutput {
        anchors.fill: parent
        source: mediaplayer
    }

    Stereo3DVideoOutput {

    }

    Component.onCompleted: {
        console.log('done')
    }
}
