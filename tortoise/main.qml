import QtQuick 2.7
import QtQuick.Controls 2.0

import "media-player"

ApplicationWindow {
    id: window
    visible: true
    width: 640
    minimumWidth: 640
    height: 480
    minimumHeight: 480
    title: "Tortoise"

    header: MusicPlayerPanel{
        height: 100
        width: parent.width
    }

    footer: Rectangle {
        width: parent.width
        height: 20
        color: "#717171"

        Text {
            width: parent.width
            height: parent.height
            text: mainWin.status
        }
    }

    Column {
        id: column
        width: parent.width
        height: parent.height

        Row {
            width: parent.width
            height: 30

            DBasePanel {
                width: parent.width
                height: parent.height
            }

        }

        Row {
            width: parent.width
            height: parent.height - 30

            StackView {
                id: stackView
                height: parent.height
                width: parent.width - playlistPanel.width
                initialItem: "ViewPage.qml"
            }

            PlaylistPanel {
                id: playlistPanel
                width: Math.max(parent.width/3, 100)
                height: parent.height

            }
        }


    }
}
