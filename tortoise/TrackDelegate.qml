import QtQuick 2.0
import QtQuick.Controls 2.4

Rectangle {
    x: 5
    width: parent.width
    height: 20

    color: model.isSelected ? "#10893e" : "#00000000"

    Row {
        width: parent.width
        height: parent.height
        property int itemWidth: (width - 20) / 3

        Text {
            text: model.modelData.num
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            color: "#ffffff"

            width: 20
        }

        Text {
            text: model.modelData.trackname
            elide: Text.ElideRight
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            color: "#ffffff"

            width: parent.itemWidth
        }

        Text {
            text: model.modelData.album
            elide: Text.ElideRight
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            color: "#ffffff"

            width: parent.itemWidth
        }

        Text {
            text: model.modelData.artist
            elide: Text.ElideRight
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            color: "#ffffff"

            width: parent.itemWidth
        }

        spacing: 10
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: {
            listView.currentIndex = model.index

            if (mouse.button === Qt.RightButton) {
                contextMenu.popup()
                if(model.isSelected)
                    return;
            }

            if(mouse.modifiers & Qt.ControlModifier) {
                viewerModel.selectAdd(model.index)
                return;
            }

            if(mouse.modifiers & Qt.ShiftModifier) {
                viewerModel.selectTo(model.index)
                return;
            }

            viewerModel.select(model.index)
        }

        onDoubleClicked: {
            console.log(model.modelData.filename)
            viewerModel.fileToPlay(model.modelData.filename)
        }

        onPressAndHold: {
            if (mouse.source === Qt.MouseEventNotSynthesized)
                contextMenu.popup()
        }

    }

    Menu {
        id: contextMenu
//        MenuItem { text: "Отправить в плейлист" }

        MenuItem {
            text: "Добавить в плейлист"
            onTriggered: {
                viewerModel.appendSelectedToPlaylist()
            }
        }

        MenuItem {
            text: "Редактировать"
            onTriggered: {
                dialogTagEdit.itemIndex = model.index
                dialogTagEdit.open()
            }
        }
        MenuItem {
            text: "Удалить"
        }

    }

}
