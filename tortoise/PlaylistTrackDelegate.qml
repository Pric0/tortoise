import QtQuick 2.0

Item {
    width: parent.width
    height: 40

    Rectangle {
        id: selected
        visible: model.isSelected
        width: parent.width
        height: parent.height
        color: "#10893e"
    }

    Row {
        spacing: 10
        Rectangle {
            width: 40
            height: 40
            color: "grey"

            Image {
                visible: !model.isCurrent
                anchors.fill: parent
                anchors.margins: 10
                source: "qrc:/icon/icon/music.svg"
                fillMode: Image.PreserveAspectFit
            }
            Image {
                visible: model.modelData.albumCover
                anchors.fill: parent
                source: model.modelData.albumCover ? model.modelData.albumCover : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                visible: model.isCurrent
                anchors.fill: parent
                anchors.margins: 10
                source: "qrc:/icon/icon/volume-max.svg"
                fillMode: Image.PreserveAspectFit
            }

        }

        Text {
            text: model.modelData.trackname + " " +
                  model.modelData.artist /*+ " " +
                  model.modelData.filename*/
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            color: "#c6c6c6"
        }
    }

    MouseArea {
        anchors.fill: parent

        onDoubleClicked: {
            playlistModel.playTrack(model.index)
        }
    }
}
