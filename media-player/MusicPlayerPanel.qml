import QtQuick 2.9
import QtQuick.Controls 2.2

Rectangle {
    id: root
    height: 100
    color: "#141414"
    property alias songLabelContainer: songLabelContainer
    width: parent.width

    Row {
        id: row1
        width: parent.width
        height: parent.height

        Item {
            width: height
            height: parent.height

            Rectangle {
                anchors.fill: parent
                anchors.margins: 5
                color: "#b6b6b6"

                Image {
                    anchors.fill: parent
                    anchors.margins: 20
                    source: "qrc:/icon/icon/music.svg"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    anchors.fill: parent
                    visible: audioPlayer.currentTrack.albumCover
                    source: audioPlayer.currentTrack.albumCover
                    fillMode: Image.PreserveAspectFit
                }

            }
        }

        Column {
            width: parent.width - height
            height: parent.height
            clip: true

            Row {
                width: parent.width
                height: parent.height -38
                spacing: 0

                Item {
                    id: songLabelContainer
                    clip: true
                    width: parent.width - 150
                    height: parent.height

                    onWidthChanged: {
                        songNameLabel.x = 0
                        animation.restart()
                    }

                    Text {
                        id: songNameLabel
                        height: parent.height
                        text: audioPlayer.currentTrack.trackname + " - " + audioPlayer.currentTrack.artist
                        font.pointSize: 14
                        verticalAlignment: Text.AlignVCenter
                        color: "#b6b6b6"

                        onWidthChanged: {
                            songNameLabel.x = 0
                            animation.restart()
                        }

                    }

                    SequentialAnimation {
                        id: animation
                        running: (songLabelContainer.width - songNameLabel.width) < 0
                        loops: Animation.Infinite

                        PauseAnimation {
                            duration: 2000
                        }
                        ParallelAnimation {
                            XAnimator {
                                target: songNameLabel
                                from: 0
                                to: songLabelContainer.width - songNameLabel.width
                                duration: 5000
                            }
                        }
                        PauseAnimation {
                            duration: 1000
                        }
                        ParallelAnimation {
                            XAnimator {
                                target: songNameLabel
                                from: songLabelContainer.width - songNameLabel.width
                                to: 0
                                duration: 5000
                            }
                        }
                    }

                }

                Column {
                    id: column
                    width: 150
                    height: parent.height

                    Row {
                        id: row
                        height: parent.height - 20

                        Button {
                            id: butPrevious
                            width: 50
                            height: parent.height
                            icon.source: "qrc:/icon/icon/rewind-b.svg"
                            icon.color: "#b6b6b6"
                            background: Rectangle {
                                anchors.fill: parent
                                color: "#141414"
                            }

                            onClicked: playlistModel.playPrev()
                        }

                        Button {
                            id: butPlayPause
                            width: 50
                            height: parent.height
                            icon.source: audioPlayer.isPlaying ?
                                             "qrc:/icon/icon/pause.svg" : "qrc:/icon/icon/play.svg"
                            icon.color: "#b6b6b6"
                            background: Rectangle {
                                anchors.fill: parent
                                color: "#141414"
                            }

                            onClicked: {
                                audioPlayer.isPlaying ? audioPlayer.stop() : audioPlayer.unpause()
                            }
                        }

                        Button {
                            id: butNext
                            width: 50
                            height: parent.height
                            icon.source: "qrc:/icon/icon/rewind-f.svg"
                            icon.color: "#b6b6b6"
                            background: Rectangle {
                                anchors.fill: parent
                                color: "#141414"
                            }

                            onClicked: playlistModel.playNext()
                        }
                    }

                    Text {
                        width: parent.width
                        height: 20
                        color: "#b6b6b6"
                        text: msToTime(control.value) + ' / ' + msToTime(control.to)
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 12

                        function msToTime(duration) {
                            var seconds = parseInt((duration) % 60),
                                    minutes = parseInt((duration/(60)) % 60),
                                    hours = parseInt((duration/(60 * 60)) % 24);

                            hours = (hours < 10) ? "0" + hours : hours;
                            minutes = (minutes < 10) ? "0" + minutes : minutes;
                            seconds = (seconds < 10) ? "0" + seconds : seconds;

                            return hours + ":" + minutes + ":" + seconds;
                        }

                    }
                }



            }

            Row {
                width: parent.width
                height: 38


                Slider {
                    id: control
                    width: parent.width
                    value: if(audioPlayer) {
                               if(!pressed)
                                   return audioPlayer.position
                               return value
                           } else return 0
                    to: audioPlayer.duration
                    snapMode: Slider.SnapOnRelease

                    background: Rectangle {
                        x: control.leftPadding
                        y: control.topPadding + control.availableHeight / 2 - height / 2
                        implicitWidth: 200
                        implicitHeight: 10
                        width: control.availableWidth
                        height: implicitHeight
                        radius: 2
                        color: "#b4b4b4"

                        Rectangle {
                            width: control.visualPosition * parent.width
                            height: parent.height
                            color: "#10893e"
                            radius: 2
                        }
                    }

                    handle: Rectangle {
                        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
                        y: control.topPadding + control.availableHeight / 2 - height / 2
                        implicitWidth: 26
                        implicitHeight: 26
                        radius: 13
                        color: control.pressed ? "#10893e" : "#b6b6b6"

                        border.color: "#363636"

                    }

                    onPressedChanged: {
                        if(!pressed)
                            audioPlayer.play(value+1)
                    }

                }

            }


        }

    }


}






