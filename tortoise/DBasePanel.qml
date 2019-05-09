import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.3

Item {
    height: 40
    Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: panel.width
        contentHeight: height

        Row {
            id: panel
            height: parent.height
            width: childrenRect.width

            Repeater {
                height: parent.height
                model: dbaseManager.dbaseList
                delegate: AbstractButton {
                    height: parent.height
                    width: childrenRect.width

                    background: Rectangle {
                        width: row.width + 10
                        height: row.height
                        color: dbaseManager.selected === model.index ? "#363636" : "#252525"
                        border.color: dbaseManager.selected === model.index ? "#292929" : color
                    }

                    Row {
                        x: 5
                        id: row
                        height: parent.height

                        Text {
                            height: parent.height
                            text: modelData.name
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 12
                            color: "#b6b6b6"
                        }

                    }

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.MiddleButton | Qt.RightButton

                        onClicked: {
                            if (mouse.button === Qt.RightButton) {
                                contextMenu.popup()
                                return;
                            }

                            if (mouse.button === Qt.MiddleButton) {
                                dbaseManager.remove(model.index)
                                return;
                            }

                            dbaseManager.select(model.index)
                        }

                        onPressAndHold: contextMenu.popup()
                    }

                    Menu {
                        id: contextMenu
                        MenuItem {
                            text: "Выбрать";
                            onTriggered: dbaseManager.select(model.index)
                        }

                        MenuItem {
                            text: "Сканировать содержимое";
                            onTriggered: dbaseManager.scan(model.index)
                        }

                        MenuItem {
                            text: "Зыкрыть"
                            onTriggered: dbaseManager.remove(model.index)
                        }

                    }

                }

            }

            Item {
                width: height - 5
                height: parent.height

                Button {
                    anchors.fill: parent
                    anchors.topMargin: 5
                    anchors.bottomMargin: 5
                    anchors.leftMargin: 5

                    hoverEnabled: true
                    contentItem: Text {
                        text: "+"
                        color: "#b6b6b6"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        width: parent.width
                        height: parent.height
                        color: parent.hovered ? "#10893e" : "transparent"
                    }

                    onClicked: fileDialog.open()
                }

                FileDialog {
                    id: fileDialog
                    title: "Выберите музыкальный каталог"
                    selectFolder: true
                    selectExisting: true
                    selectMultiple: false
                    onAccepted: {
                        dbaseManager.openFolder(fileDialog.fileUrl)
                    }
                }

            }

        }

    }

}
