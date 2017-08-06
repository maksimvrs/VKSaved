import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.3
import "Qml" as Page

ApplicationWindow {
    id: main
    visible: true
    width: 360
    height: 520
    title: qsTr("VK Saved")

    Material.theme: Material.Light
    Material.accent: "#4a7fbc"

    header: Page.Toolbar {
        id: toolbar
        visible: false
        settingsButton.onClicked:
            stackView.push("qrc:/Qml/Settings.qml", {visible: true})
    }

    Page.Drawer {
        id: drawer
    }

    Component.onCompleted: {
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
                    login.clicked
                    captchaDialog.clear()
                }
                onRejected: {
                    login.loading.visible = false
                    login.loading.running = false
                }
            }

            onClicked: {
                login.loading.visible = true
                login.loading.running = true
                getAccessToken()
            }

            onCaptchaRequest: {
                captchaDialog.source = login.captchaSource
                captchaDialog.open()
            }

            onConnectionComplete: {
                stackView.push("Qml/Saved.qml", {visible: true})
                toolbar.visible = true

                login.loading.visible = false
                login.loading.running = false
                login.clear()
            }
        }
    }
}
