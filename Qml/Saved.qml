import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import SavedBackend 1.0

ListView {
    id: listView
    Material.background: "Gray"
    spacing: 20
    model: ListModel {
        ListElement {
            profilePhoto: "http://vk.com/images/camera_c.gif"
            profileName: "Profile Name"
            image: "https://upload.wikimedia.org/wikipedia/en/a/a9/Example.jpg"
        }
        ListElement {
            profilePhoto: "http://vk.com/images/camera_c.gif"
            profileName: "Profile Name"
            image: "https://upload.wikimedia.org/wikipedia/en/a/a9/Example.jpg"
        }
    }

    delegate: Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        height: header.height + image.height + footer.height

        ColumnLayout {
            width: listView.width

            ToolBar {
                id: header

                Layout.fillWidth: true

                background: Rectangle {
                    anchors.fill: parent
                    color: "white"
                }

                padding: {
                    left: 10
                    right: 10
                    top: 10
                }

                RowLayout {
                    spacing: 20
                    anchors.fill: parent

                    ToolButton {
                        Layout.maximumHeight: 50
                        Layout.maximumWidth: 50

                        contentItem: Image {
                            id: profilePhoto
                            fillMode: Image.PreserveAspectFit
                            anchors.fill: parent
                            source: model.profilePhoto
                            layer.enabled: true
                            layer.effect: OpacityMask {
                                maskSource: mask
                            }
                        }
                        Rectangle {
                            id: mask
                            width: profilePhoto.width
                            height: profilePhoto.height
                            radius: 360
                            visible: false
                        }

                    }

                    Label {
                        id: profileName
                        text: model.profileName
                        font.pixelSize: 20
                        font.bold: true
                        color: "#5f95d0"
                        elide: Label.ElideRight
                        Layout.fillWidth: true
                    }

                    ToolButton {
                        contentItem: Image {
                            fillMode: Image.Pad
                            horizontalAlignment: Image.AlignHCenter
                            verticalAlignment: Image.AlignVCenter
                            source: "qrc:/Images/menu_small.svg"
                        }

                        onClicked: optionsMenu.open()

                        Menu {
                            id: optionsMenu
                            x: listView.width - width
                            transformOrigin: Menu.TopRight

                            MenuItem {
                                text: "Settings"
                                onTriggered: settingsDialog.open()
                            }
                            MenuItem {
                                text: "About"
                                onTriggered: aboutDialog.open()
                            }
                        }
                    }
                }
            }

            Image {
                id: image
                smooth: true
                fillMode: Image.PreserveAspectFit
                Layout.fillWidth: true
                anchors {
                    top: header.bottom
                    bottom: footer.top
                }
                source: model.image
            }

            RowLayout {
                id: footer
                Layout.fillWidth: true
                spacing: 40

                ToolButton {
                    id: like

                    property bool ok: false // get value

                    Layout.fillWidth: true

                    contentItem: Image {
                        fillMode: Image.Pad
                        source: like.ok ? "qrc:/Images/likeOK.svg" : "qrc:/Images/like.svg"
                    }

                    background: Rectangle {
                        implicitWidth: 40
                        implicitHeight: 40
                        color: Qt.darker("#33333333", like.enabled && (like.checked || like.highlighted) ? 1.5 : 1.0)
                        opacity: enabled ? 1 : 0.3
                        visible: like.down || (like.enabled && (like.checked || like.highlighted))
                    }

                    onClicked: {
                        ok = ok ? false : true
                    }
                }


                ToolButton {
                    id: save

                    property bool ok: false // get value

                    Layout.fillWidth: true

                    contentItem: Image {
                        fillMode: Image.Pad
                        source: save.ok ? "qrc:/Images/saveOK.svg" : "qrc:/Images/save.svg"
                    }

                    background: Rectangle {
                        implicitWidth: 40
                        implicitHeight: 40
                        color: Qt.darker("#33333333", save.enabled && (save.checked || save.highlighted) ? 1.5 : 1.0)
                        opacity: enabled ? 1 : 0.3
                        visible: save.down || (save.enabled && (save.checked || save.highlighted))
                    }

                    onClicked: {
                        ok = ok ? false : true
                    }
                }
            }
        }
    }
}


