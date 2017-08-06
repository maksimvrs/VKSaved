import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Dialog {
    property alias key: textField.text
    property alias source: image.source

    function clear() {
        textField.clear()
    }

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    standardButtons: Dialog.Ok | Dialog.Cancel

    ColumnLayout {
        spacing: 20
        anchors.fill: parent

        BusyIndicator {
            id: busyIndicator
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            running: image.status === Image.Loading
        }

        Image {
            id: image
            fillMode: Image.PreserveAspectFit
            Layout.fillWidth: true
            onProgressChanged: {
                if(progress == 1.0)
                    busyIndicator.visible = false;
            }
        }

        TextField {
            id: textField
            placeholderText: "Captcha"
            Layout.fillWidth: true
        }
    }
}
