import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard 2.4

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Stack")

    background: Image {
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/background.jpg"
    }

//    header: ToolBar {
//        contentHeight: toolButton.implicitHeight

//        ToolButton {
//            id: toolButton
//            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
//            font.pixelSize: Qt.application.font.pixelSize * 1.6
//            onClicked: {
//                if (stackView.depth > 1) {
//                    stackView.pop()
//                } else {
//                    drawer.open()
//                }
//            }
//        }

//        Label {
//            text: stackView.currentItem.title
//            anchors.centerIn: parent
//        }
//    }

    StackView {
        id: stackView
        initialItem: videoMain
        anchors.fill: parent
    }

    Component {
        id: videoMain

        UI_VideoMain {
            width: window.width
            height: window.height
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
