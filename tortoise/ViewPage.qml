import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    id: page
    width: parent.width
    height: parent.height

    Column {
        width: parent.width
        height: parent.height
        visible: !viewerModel.isEmpty

        Rectangle {
            width: parent.width
            height: 30
            color: "#222222"

            Row {
                anchors.fill: parent

                SearchInput {
                    id: searchInput
                    width: parent.width - coutnText.width

                    text: viewerModel.searchFilter
                    onTextChanged: viewerModel.searchFilter = text
                }

                Text {
                    id: coutnText
                    height: parent.height
                    color: "#c4c4c4"
                    text: "Всего: " + listView.count
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 16
                }
            }
        }

        Row {
            height: parent.height - 30
            clip: true
            width: parent.width

            ListView {
                id: artistFilterView
                width: Math.max(parent.width / 5, 120)
                height: parent.height
                cacheBuffer: 0
                boundsBehavior: Flickable.StopAtBounds
                clip: true
                model: viewerArtistsModel
                delegate: ArtistFilterDelegate {
                    name: modelData.name
                    albums: "Альбомов: " + modelData.albums
                }

                header: ArtistFilterDelegate {
                    albums: ""
                    name: ""
                    color: viewerArtistsModel.isEmptyFilter ? "#10893e" : "#00000000"
                }

            }

            ListView {
                id: listView
                y: -180
                clip: false
                height: parent.height + 180
                cacheBuffer: 40
                width: parent.width - artistFilterView.width
                model: viewerModel
                delegate: TrackDelegate { }
                boundsBehavior: Flickable.StopAtBounds // +180

                ScrollBar.vertical: scrollBar

                header: Item {
                    height: 180
                    width:parent.width
                }

                footerPositioning: ListView.InlineFooter
                footer: Item {
                    height: 180
                    width:parent.width
                }
            }

        }

    }

    ScrollBar {
        id: scrollBar
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    Dialog {
        id: dialogTagEdit
        title: "Редактор информации"
        x: 5
        y: 5
        width: parent.width - 10
        height: parent.height - 10
        modal: true

        property int itemIndex: -1
        onItemIndexChanged: {
            var track = viewerModel.data(viewerModel.index(itemIndex, 0), 256)
            currentDialogItem.artist = track.artist
            currentDialogItem.album = track.album
            currentDialogItem.number = track.num
            currentDialogItem.name = track.trackname
            currentDialogItem.genre = track.genres
            currentDialogItem.filename = track.filename
        }

        contentItem: Flickable {
            width: dialogTagEdit.contentWidth
            height: dialogTagEdit.contentHeight
            contentWidth: width - 15
            contentHeight: currentDialogItem.height
            clip: true

            DialogTagEdit {
                id: currentDialogItem
            }

            ScrollBar.vertical: ScrollBar { }
        }

        standardButtons: Dialog.Save | Dialog.Discard

        onAccepted: console.log("Ok clicked")
        onDiscarded: { close() }
    }

}

/*##^## Designer {
    D{i:5;anchors_height:30}D{i:6;anchors_height:400;anchors_width:200}
}
 ##^##*/
