import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Dialog {
    property alias key: key
    property alias captchaImage: captchaImage

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    standardButtons: Dialog.Ok | Dialog.Cancel

    ColumnLayout {
        spacing: 20
        anchors.fill: parent
        Image {
            id: captchaImage
            fillMode: Image.PreserveAspectFit
            Layout.fillWidth: true
        }
        TextField {
            id: key
            placeholderText: "Captcha"
            Layout.fillWidth: true
        }
    }
}
