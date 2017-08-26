import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.2
import SavedBackend 1.0

ListView {
    id: root

    property bool delegateVisible: false
    property alias loading: progressBar.visible

    function start() {
        backend.update()
    }

    function readAccessToken() {
        backend.readAccessToken()
    }

    Material.background: "Gray"
    spacing: 10
    smooth: true

    model: backend.model

    cacheBuffer: Screen.desktopAvailableHeight * 3

    Component.onCompleted: {
        currentIndex = -1
    }

    SavedBackend {
        id: backend
        onProgressChanged: {
            ++progressBar.value
            if (progressBar.value === progressBar.to) {
                progressBar.visible = false
                root.delegateVisible = true
            }
        }
    }

    ProgressBar {
        id: progressBar
        to: backend.accountsCount - 1
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    onDragEnded: if (refresh.refresh) {
                     backend.updateSaved()
                     console.log("OK")
                 }

    Refresh {
        id: refresh
        y: -root.contentY - height
    }

    delegate: Rectangle {
        visible: delegateVisible
        anchors.left: parent.left
        anchors.right: parent.right
        height: header.height + image.height + footer.height

        layer.enabled: true
        layer.effect: DropShadow {
            color: "#9B9B9B"
            transparentBorder: true
            verticalOffset: 1
        }

        ColumnLayout {
            width: root.width
            spacing: 0

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

                    ColumnLayout {
                        spacing: 5

                        Label {
                            id: profileName
                            text: model.profileName
                            font.pixelSize: 17
                            font.bold: true
                            color: "#5f95d0"
                            elide: Label.ElideRight
                            Layout.fillWidth: true
                        }

                        Label {
                            id: date
                            text: model.date
                            font.pixelSize: 13
                            color: "#9B9B9B"
                            elide: Label.ElideRight
                            Layout.fillWidth: true
                        }
                    }

                    ToolButton {
                        contentItem: Image {
                            fillMode: Image.Pad
                            horizontalAlignment: Image.AlignHCenter
                            verticalAlignment: Image.AlignVCenter
                            source: "qrc:/Images/menuSmall.svg"
                        }

                        onClicked: optionsMenu.open()

                        Menu {
                            id: optionsMenu
                            x: root.width - width
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

            Rectangle {
                id: busyIndicator
                Layout.fillWidth: true
                height: parent.width * model.ratio
                BusyIndicator {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    running: image.status === Image.Loading
                    height: 300
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

                onSourceChanged: {
                    busyIndicator.visible = true;
                }

                onProgressChanged: {
                    if(progress == 1.0)
                        busyIndicator.visible = false;
                }

                sourceSize.height: image.width * model.ratio
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
                        sourceSize: Qt.size(20, 20)
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
                        sourceSize: Qt.size(20, 20)
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


