import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Dialog {
    property alias captchaImage: captchaImage

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    parent: ApplicationWindow.overlay

//    focus: true
    modal: true
    title: "Captcha"
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
//            focus: true
            placeholderText: "Captcha"
            Layout.fillWidth: true
        }
    }
}
