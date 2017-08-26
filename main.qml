import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

import "Qml" as Page
import SavedBackend 1.0

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
            stackView.push(settings, {visible: true})
    }

    Page.Settings {
        id: settings
    }

    Page.Drawer {
        id: drawer
    }

    Page.Saved {
        id: saved
        function run() {
            stackView.push(saved)
            toolbar.visible = true
            toolbar.settingsButton.visible = true
            saved.readAccessToken()
//            saved.loading = true
            saved.delegateVisible = true
            saved.start()
        }
    }

    Component.onCompleted: {
        if (login.haveAccessToken) {
            saved.run()

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
                saved.run()

                login.loading.visible = false
                login.loading.running = false
                login.clear()
            }
        }
    }
}
