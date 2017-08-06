import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

ToolBar {
    Material.background: "#5f95d0"

    property alias settingsButton: settingsButton

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
                    settingsButton.visible = true
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            id: statusLabel
            text: stackView.depth > 2 ? "Настройки" : "VK Saved"
            font.pixelSize: 20
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        ToolButton {
            id: settingsButton
            contentItem: Image {
                fillMode: Image.Pad
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: "qrc:/Images/settings.svg"
                sourceSize: Qt.size(25, 25)
            }
            onClicked: {
                settingsButton.visible = false
            }
        }
    }
}
