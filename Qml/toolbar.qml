import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1

ToolBar {
    Material.background: "#5f95d0"

    RowLayout {
        spacing: 20
        anchors.fill: parent

        ToolButton {
            //Image (Три полоски и назад)
            contentItem: Image {
                fillMode: Image.Pad
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: stackView.depth > 2 ? "images/back.png" : "images/drawer.png"
            }

//            contentItem: Rectangle {
//                color: "white"
//            }

            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                    listView.currentIndex = -1
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            id: statusLabel
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        ToolButton {
            contentItem: Image {
                fillMode: Image.Pad
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: "qrc:/images/menu.png"
            }
            onClicked: stackView.push("Qml/settings.qml", {visible: true})
        }
    }
}
