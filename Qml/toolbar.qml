import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

ToolBar {
    Material.background: "#5f95d0"

    RowLayout {
        spacing: 20
        anchors.fill: parent

        ToolButton {
            contentItem: Image {
                fillMode: Image.Pad
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: stackView.depth > 2 ? "qrc:/Images/back.svg" : "qrc:/Images/menu.svg"
                sourceSize: Qt.size(25, 25)
            }

            onClicked: {
                if (stackView.depth > 2) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            id: statusLabel
            text: "VK Saved"
            font.pixelSize: 20
            font.bold: true
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        ToolButton {
            contentItem: Image {
                fillMode: Image.Pad
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: stackView.depth <= 2 ? "qrc:/Images/settings.svg" : ""
                sourceSize: Qt.size(25, 25)
            }
            onClicked: stackView.push("qrc:/Qml/Settings.qml", {visible: true})
        }
    }
}
