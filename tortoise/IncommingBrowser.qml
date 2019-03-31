import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

Page {
    title: "Входящие"

    Row {
        id: row
        anchors.fill: parent

        ListView {
            id: listView
            x: 0
            y: 0
            width: 200
            height: parent.height
            clip: true
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row2
                    Rectangle {
                        width: 40
                        height: 40
                        color: artistImage
                    }

                    Text {
                        text: artist
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    spacing: 10
                }
            }
            model: ListModel {
                ListElement {
                    artist: "Исполнитель 1"
                    artistImage: "grey"
                }

                ListElement {
                    artist: "Исполнитель 2"
                    artistImage: "red"
                }

                ListElement {
                    artist: "Исполнитель 3"
                    artistImage: "blue"
                }

                ListElement {
                    artist: "Исполнитель 4"
                    artistImage: "green"
                }
            }
        }

        ListView {
            id: listView1
            x: 0
            y: 0
            width: parent.width - 200
            height: parent.height
            clip: true
            delegate: Item {
                x: 25
                width: 80
                height: 10
                Row {
                    Text {
                        text: trackName
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    spacing: 10
                }
            }
            section.property: "album"
            section.criteria: ViewSection.FullString
            section.delegate: Item {
                x: 5
                y: 5
                width: 80
                height: 10
                Row {
                    Text {
                        text: section
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

            model: ListModel {
                ListElement {
                    album: "Album 1"
                    trackName: "track 1"
                }

                ListElement {
                    album: "Album 1"
                    trackName: "track 2"
                }

                ListElement {
                    album: "Album 1"
                    trackName: "track 3"
                }

                ListElement {
                    album: "Album 2"
                    trackName: "track 1"
                }
            }
        }
    }

}
