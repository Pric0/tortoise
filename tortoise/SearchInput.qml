import QtQuick 2.0

Item {
    height: parent.height
    width: parent.width
    property alias text: textInput.text

    Rectangle {
        anchors.fill: parent
        anchors.margins: 5
        color: "#00000000"
        radius: 5
        border.color: "#c4c4c4"
        clip: true

        TextInput {
            id: textInput
            text: ""
            anchors.fill: parent
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            font.pixelSize: 16
            selectByMouse: true
            activeFocusOnPress: true
            color: "#c4c4c4"
        }

    }

}
