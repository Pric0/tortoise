import QtQuick 2.0

Rectangle {
    x: 5
    width: parent.width
    height: 30

    color: model.isSelected ? "#10893e" : "#00000000"

    property string name: artistName.text
    property string albums: albumCount.text

    Row {
        spacing: 10
        width: parent.width
        height: parent.height

        Column {
            width: parent.width - 50
            height: parent.height

            Text {
                id: artistName
                text: name ? (name == "NULL" ? "Неизвестный исполнитель" : name) : "Все исполнители"
                height: parent.height / 2

                font.bold: true
                color: "#c4c4c4"
            }

            Text {
                id: albumCount
                height: parent.height / 2

                color: "#c6c6c6"
                text: albums
            }
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            viewerArtistsModel.selectArtist(name)
        }
    }
}
