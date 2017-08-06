import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

Item {
    Button {
        id: button
        text: "Выйти"
        font.bold: true
        highlighted: true
        Material.background: "#5f95d0"
        Layout.fillWidth: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        onClicked: {
            login.exit()
            stackView.pop()
            toolbar.visible = false
            stackView.pop()
        }
    }
}
