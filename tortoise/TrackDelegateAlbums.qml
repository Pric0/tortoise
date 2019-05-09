import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    id: m_Item

    width: parent.width
    height: childrenRect.height

    Column {
        width: parent.width
        height: childrenRect.height
        spacing: 1

        Item {
            width: parent.width
            height: {
                if(model.index <= 0)
                    return 0

                if(viewerModel.data(viewerModel.index(model.index-1, 0, 0), 256).albumId
                        === model.modelData.albumId)
                    return 0

                var albCount = viewerModel.data(
                            viewerModel.index(model.index-1, 0, 0), 256).albumTrackCount

                var needTracks = parseInt((albumImage.width - 20)/20)

                if(albCount > needTracks)
                    return 0

                return needTracks * 20
            }
        }

        Column {
            spacing: 0
            width: parent.width
            height: visible ? 34 : 0
            visible: {
                if(model.index <= 0)
                    return true

                if(viewerModel.data(viewerModel.index(model.index-1, 0, 0), 256).artist
                        !== model.modelData.artist)
                    return true

                return false
            }

            Text {
                x: 5
                width: parent.width-5
                text: model.modelData.artist ? model.modelData.artist : "Неизвестный исполнитель"
                font.pointSize: 16
                fontSizeMode: Text.HorizontalFit
                verticalAlignment: Text.AlignVCenter
                color: "#b6b6b6"

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    onClicked: {
                        if (mouse.button === Qt.RightButton) {
                            contextMenu.popup()
                            if(model.isSelected)
                                return;
                        }

                        viewerModel.select(model.index)

                        var indexOfNextItem = model.index
                        while(viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256) &&
                            viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256).artist
                              === model.modelData.artist)
                            indexOfNextItem++

                        viewerModel.selectTo(indexOfNextItem)

                    }

                    onDoubleClicked: {
                        viewerModel.select(model.index)

                        var indexOfNextItem = model.index
                        while(viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256) &&
                            viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256).artist
                              === model.modelData.artist)
                            indexOfNextItem++

                        viewerModel.selectTo(indexOfNextItem)

                        viewerModel.appendSelectedToPlaylist()
                    }

                    onPressAndHold: {
                        if (mouse.source === Qt.MouseEventNotSynthesized)
                            contextMenu.popup()
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: 1
                color: "#252525"
            }
        }

        Row {
            x: 5
            spacing: 10
            width: parent.width-5
            height: 20
            visible: {
                if(model.index <= 0)
                    return true

                if(viewerModel.data(viewerModel.index(model.index-1, 0, 0), 256).albumId
                        !== model.modelData.albumId)
                    return true

                return false
            }

            Rectangle {
                id: albumImage
                width: Math.min(parent.width / 3, 200)
                height: width
                color: "#b6b6b6"

                Image {
                    anchors.fill: parent
                    anchors.margins: 40
                    source: "qrc:/icon/icon/music.svg"
                    fillMode: Image.PreserveAspectFit
                }
                Image {
                    visible: model.modelData.albumCover
                    anchors.fill: parent
                    source: model.modelData.albumCover ? model.modelData.albumCover : ""
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    onClicked: {
                        if (mouse.button === Qt.RightButton) {
                            contextMenu.popup()
                            if(model.isSelected)
                                return;
                        }

                        viewerModel.select(model.index)

                        var indexOfNextItem = model.index
                        while(viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256) &&
                            viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256).albumId
                              === model.modelData.albumId)
                            indexOfNextItem++

                        viewerModel.selectTo(indexOfNextItem)

                    }

                    onDoubleClicked: {
                        viewerModel.select(model.index)

                        var indexOfNextItem = model.index
                        while(viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256) &&
                            viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256).albumId
                              === model.modelData.albumId)
                            indexOfNextItem++

                        viewerModel.selectTo(indexOfNextItem)

                        viewerModel.appendSelectedToPlaylist()
                    }

                    onPressAndHold: {
                        if (mouse.source === Qt.MouseEventNotSynthesized)
                            contextMenu.popup()
                    }
                }
            }

            Column {
                id: artistColumn
                width: parent.width - 210
                height: 20

                Text {
                    width: parent.width
                    height: 20
                    text: (model.modelData.album ? model.modelData.album : "Неизвестный альбом")
                          + " (" + model.modelData.albumTrackCount + ")"
                    font.pointSize: 12
                    verticalAlignment: Text.AlignVCenter
                    color: "#b6b6b6"

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton

                        onClicked: {
                            if (mouse.button === Qt.RightButton) {
                                contextMenu.popup()
                                if(model.isSelected)
                                    return;
                            }

                            viewerModel.select(model.index)

                            var indexOfNextItem = model.index
                            while(viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256) &&
                                viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256).albumId
                                  === model.modelData.albumId)
                                indexOfNextItem++

                            viewerModel.selectTo(indexOfNextItem)

                        }

                        onDoubleClicked: {
                            viewerModel.select(model.index)

                            var indexOfNextItem = model.index
                            while(viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256) &&
                                viewerModel.data(viewerModel.index(indexOfNextItem+1, 0, 0), 256).albumId
                                  === model.modelData.albumId)
                                indexOfNextItem++

                            viewerModel.selectTo(indexOfNextItem)

                            viewerModel.appendSelectedToPlaylist()
                        }

                        onPressAndHold: {
                            if (mouse.source === Qt.MouseEventNotSynthesized)
                                contextMenu.popup()
                        }
                    }
                }
            }
        }

        Rectangle {
            x: albumImage.width + 15
            width: parent.width - x
            height: 20
            color: model.isSelected ? "#10893e" : "#00000000"

            Row {
                anchors.fill: parent
                spacing: 10

                Text {
                    height: 20
                    text: model.modelData.num
                    verticalAlignment: Text.AlignVCenter
                    color: "#b6b6b6"
                }

                Text {
                    height: 20
                    text: model.modelData.trackname
                    verticalAlignment: Text.AlignVCenter
                    color: "#b6b6b6"
                }

            }

            MouseArea {
                id: trackMouseArea
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                drag.target: draggable

                onClicked: {
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

                onDoubleClicked:
                    viewerModel.fileToPlay(model.modelData.filename)

                onPressAndHold: {
                    if (mouse.source === Qt.MouseEventNotSynthesized)
                        contextMenu.popup()
                }

            }

            Menu {
                id: contextMenu

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


    }

    Item {
        id: draggable
//        anchors.fill: parent
        Drag.active: trackMouseArea.drag.active
        Drag.hotSpot.x: 0
        Drag.hotSpot.y: 0
        Drag.mimeData: { "text/plain": "file:///1.mp3" }
        Drag.dragType: Drag.Automatic
//        Drag.onDragFinished: if (dropAction == Qt.MoveAction) item.display = ""
    }

}
