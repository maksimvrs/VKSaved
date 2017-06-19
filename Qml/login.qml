import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.3
import LoginBackend 1.0

Rectangle {
    property alias button: button
    property alias loginBackend: loginBackend
    property alias captchaImage: loginBackend.captchaSource

    LoginBackend {
        id: loginBackend
        login: loginField.text
        password: passField.text
    }

    ColumnLayout {
        anchors {
            fill: parent
            bottomMargin: 40
            leftMargin: 40
            rightMargin: 40
        }
        spacing: 10

        Image {
            id: logo
            source: "../Images/logo.png"
            fillMode: Image.PreserveAspectFit
            Layout.fillWidth: true
            Layout.maximumHeight: parent.height / 4
        }

        TextField {
            id: loginField
            placeholderText: "Email или телефон"
            maximumLength: 35
            Layout.fillWidth: true
        }

        TextField {
            id: passField
            echoMode: TextInput.Password
            placeholderText: "Пароль"
            maximumLength: 25
            Layout.fillWidth: true
        }
        Button {            
            id: button
            text: "Войти"
            font.bold: true
            highlighted: true
            Material.background: "#5f95d0"
            Layout.fillWidth: true
        }
    }
}
