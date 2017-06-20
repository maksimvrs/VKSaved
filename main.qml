import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.3
import "Qml" as Page

ApplicationWindow {
    visible: true
    width: 360
    height: 520
    title: qsTr("VK Saved")

    Material.theme: Material.Light
    Material.accent: "#4a7fbc"

    header: Page.Toolbar {
        id: toolbar
        visible: false
    }

    onSceneGraphInitialized: {
        if (login.haveAccessToken) {
            stackView.push("Qml/Saved.qml", {visible: true})
            toolbar.visible = true
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent 

        initialItem: Page.Login {
            id: login
            visible: true

            Page.Captcha {
                id: captchaDialog
                onAccepted: {
                    login.captchaInput(key)
                }
            }

            onClicked: {
                getAccessToken()
            }

            onCaptchaRequest: {
                captchaDialog.source = login.captchaSource
                captchaDialog.open()
            }

            onConnectionComplete: {
                stackView.push("Qml/Saved.qml", {visible: true})
                toolbar.visible = true
            }
        }
    }
}
