import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Tortoise")

    header: ToolBar {
        contentHeight: 40

        Row {

            ToolButton {
                text: "Коллекция"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                checked: text === stackView.currentItem.title
                onClicked: {
                    stackView.replace("qrc:/MusicBrowser.qml")
                }
            }

            ToolButton {
                text: "Входящие"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                checked: text === stackView.currentItem.title
                onClicked: {
                    stackView.replace("qrc:/IncommingBrowser.qml")
                }
            }

        }
    }

    Column {
        anchors.fill: parent

        StackView {
            id: stackView
            initialItem: "MusicBrowser.qml"
            width: parent.width
            height: parent.height - 40
        }

        Player {
            id: player
            width: parent.width
            height: 40
        }
    }
}
/*##^## Designer {
    D{i:33;anchors_height:400;anchors_width:200}
}
 ##^##*/

/*##^## Designer {
    D{i:33;anchors_height:400;anchors_width:200}
}
 ##^##*/
