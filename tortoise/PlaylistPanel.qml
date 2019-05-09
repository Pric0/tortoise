import QtQuick 2.0
import QtQuick.Controls 2.4

Column {
    width: parent.width
    height: parent.height

    Rectangle {
        width: parent.width
        height: 30
        color: "#222222"

        Text {
            id: coutnText
            height: parent.height
            width: parent.width
            color: "#c4c4c4"
            text: "Плейлист (" + playlistView.count + ")"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 16
        }


        Button {
            anchors.right: parent.right
            text: "x"
            onClicked: playlistModel.clearModel();
        }
    }

    ListView {
        id: playlistView
        width: parent.width
        height: parent.height - 30
        spacing: 3
        clip: true
        model: playlistModel
        delegate: PlaylistTrackDelegate { }

        Rectangle {
            visible: playlistView.count == 0
            color: "#00000000"
            border.color: "#c4c4c4"
            border.width: 2
            anchors.fill: parent
            anchors.margins: 10

            Text {
                text: qsTr("Список воспроизведения пуст")
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 16
                color: "#c4c4c4"
            }

        }

        Rectangle {
            visible: dropArea.containsDrag
            color: "#b3c4c4c4"
            border.color: "#c6c6c6"
            border.width: 2
            anchors.fill: parent
            anchors.margins: 10

            Text {
                text: qsTr("Добавить")
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 20
                color: "#ffffff"
            }

        }

        DropArea {
            id: dropArea
            anchors.fill: parent
//                keys: ["text/plain"]
//                onEntered: {
//                    drag.accepted = false
//                }
            onDropped:{
//                if (drop.proposedAction == Qt.MoveAction ||
//                        drop.proposedAction == Qt.CopyAction) {
//                    drop.acceptProposedAction()

                    console.log(drop.urls)
//                    playlistModel.appendTrack(drop.urls)
//                }
            }
        }

    }




}

/*##^## Designer {
    D{i:9;anchors_height:200;anchors_width:200}
}
 ##^##*/
