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
            contentItem: Image {
                fillMode: Image.Pad
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: stackView.depth > 2 ? "qrc:/Images/back.svg" : "qrc:/Images/menu.svg"
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
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        ToolButton {
            contentItem: Image {
                fillMode: Image.Pad
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: "qrc:/Images/settings.svg"
            }
            onClicked: stackView.push("qrc:/Qml/Settings.qml", {visible: true})
        }
    }
}
