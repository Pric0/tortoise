import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    property alias artist: artist.text
    property alias album: album.text
    property alias number: number.text
    property alias name: name.text
    property alias genre: genre.text
    property alias filename: filename.text

    width: parent.width
    height: row.implicitHeight

    Row {
        id: row
        anchors.fill: parent
        spacing: 5

        Column {
            id: col1
            width: childrenRect.width
            spacing: parent.spacing

            Repeater {
                model: ["Исполнитель: ", "Альбом: ", "Номер дорожки: ",
                        "Название дорожки: ", "Жанр: ", "Имя файла: "]
                Label {
                    height: 32
                    text: modelData
                    verticalAlignment: Text.AlignVCenter
                }
            }

        }

        Column {
            width: parent.width - col1.width - 5
            spacing: parent.spacing

            TextField {
                id: artist
                height: 32
                width: parent.width
                selectByMouse: true

            }

            TextField {
                id: album
                height: 32
                width: parent.width
                selectByMouse: true
            }

            TextField {
                id: number
                height: 32
                width: parent.width
                selectByMouse: true
                inputMethodHints: Qt.ImhDigitsOnly
                inputMask: "[000]"
            }

            TextField {
                id: name
                height: 32
                width: parent.width
                selectByMouse: true
            }

            TextField {
                id: genre
                height: 32
                width: parent.width
                selectByMouse: true
            }

            TextField {
                id: filename
                height: 32
                width: parent.width
                selectByMouse: true
            }

            Row {
                width: parent.width

                Item {
                    width: parent.width - 60
                    height: 20
                }

                Rectangle {
                    width: 30
                    height: 20
                    color: "#cfcfcf"
                    enabled: dialogTagEdit.itemIndex > 0

                    Text {
                        text: "<"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.fill: parent
                        font.pixelSize: 12
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onContainsMouseChanged:
                            containsMouse ? parent.color = "#8f8f8f" : parent.color = "#cfcfcf"

                        onClicked: {
                            if(dialogTagEdit.itemIndex <= 0)
                                return

                            listView.decrementCurrentIndex()
                            dialogTagEdit.itemIndex = dialogTagEdit.itemIndex - 1
                        }
                    }
                }

                Rectangle {
                    width: 30
                    height: 20
                    color: "#cfcfcf"
                    enabled: dialogTagEdit.itemIndex < listView.count-1

                    Text {
                        text: ">"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.fill: parent
                        font.pixelSize: 12
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onContainsMouseChanged:
                            containsMouse ? parent.color = "#8f8f8f" : parent.color = "#cfcfcf"

                        onClicked: {
                            if(dialogTagEdit.itemIndex >= listView.count-1)
                                return

                            listView.incrementCurrentIndex()
                            dialogTagEdit.itemIndex = dialogTagEdit.itemIndex + 1
                        }
                    }
                }
            }

        }

    }

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
