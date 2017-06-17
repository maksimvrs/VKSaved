import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.3

ListView {
    Material.background: "Gray"
    spacing: 20
//    model: /*data list (modelData)*/

    delegate: ItemDelegate {
        ColumnLayout {
            spacing: 20
            anchors.fill: parent

            RowLayout {
                spacing: 20
                Layout.fillWidth: true

                Image {
                    // Фото профиля
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    //                    source: // Фото
                }

                Label {
                    // Имя профиля
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    //                    text: // Имя
                }

                ToolButton {
                    // Опции
                    contentItem: Image {
                        fillMode: Image.Pad
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        //                        source: // Иконка опции
                    }
                    //                    onClicked: optionsMenu.open()

                    Menu {
                        id: optionsMenu
                        x: parent.width - width
                        transformOrigin: Menu.TopRight

                        MenuItem {
                            text: "Копировать ссылку"
//                            onTriggered: //
                        }
                        MenuItem {
                            text: "Скрыть новости источника"
                            //                            onTriggered: //
                        }
                    }
                }
            }

            Image {
                id: image
                fillMode: Image.Pad
                horizontalAlignment: Image.PreserveAspectFit
                width: parent.width
                //                source: //image
            }

            RowLayout {
                spacing: 40
                anchors.fill: parent

                ToolButton {
                    id: like
                    contentItem: Image {
                        fillMode: Image.Pad
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        //                        source: // image
                    }
                    //                    onClicked: // like
                }

                ToolButton {
                    id: comment
                    contentItem: Image {
                        fillMode: Image.Pad
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        //                        source: // image
                    }
                    //                    onClicked: // comment
                }

                ToolButton {
                    id: save
                    contentItem: Image {
                        fillMode: Image.Pad
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                        //                        source: // image
                    }
                    //                    onClicked: // save
                }
            }
        }
    }
}
