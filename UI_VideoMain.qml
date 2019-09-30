import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 600
    height: 400
    background: Item {
    }

    title: qsTr("Видео")

    Rectangle {
        id: panelRect
        x: 0
        y: parent.height - height - 10
        width: parent.width
        height: parent.height / 6
        color: "#5c545445"

        Row {
            id: row
            spacing: 5
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.fill: parent

            Button {
                height: parent.height
                text: qsTr("Браузер")
            }

            Button {
                height: parent.height
                text: qsTr("Коллекция")
            }
        }
    }

    Rectangle {
        id: dataRect
        x: 10
        y: 10
        width: parent.width - 20
        height: panelRect.y - 20
        color: "#5c545445"
        radius: 10
        clip: true

        ListView {
            id: listView
            x: 10
            y: 10
            width: parent.width - 20
            height: parent.height - 10
            clip: false
            delegate: Rectangle {
                x: 5
                width: parent.width
                height: 40
                color: index == listView.currentIndex? "#545445" : "#5c545445"
                Row {
                    Image {
                        width: 40
                        height: 40
                        source: "qrc:/movieEmpty.png"
                    }

                    Text {
                        color: "#d4d2d2"
                        text: index + ") " + display
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    spacing: 10
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true

                    onEntered: {
                        listView.currentIndex = index
                    }

                    onClicked: modelVideoView.update(display)
                }
            }
            model: modelVideoView
        }
    }

}

/*##^##
Designer {
    D{i:3;anchors_height:400;anchors_width:200}
}
##^##*/
