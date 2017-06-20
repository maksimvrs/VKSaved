import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Dialog {
    property alias key: textField.text
    property alias source: image.source

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    standardButtons: Dialog.Ok | Dialog.Cancel

    ColumnLayout {
        spacing: 20
        anchors.fill: parent
        Image {
            id: image
            fillMode: Image.PreserveAspectFit
            Layout.fillWidth: true
        }
        TextField {
            id: textField
            placeholderText: "Captcha"
            Layout.fillWidth: true
        }
    }
}
