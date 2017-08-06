import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

Drawer {
    id: drawer
    width: Math.min(parent.width, parent.height) / 3 * 2
    height: parent.height
    interactive: stackView.depth === 2

    ListView {
        id: listView

        focus: true
        currentIndex: -1
        anchors.fill: parent

        delegate: ItemDelegate {
            width: parent.width
            text: model.title
            highlighted: ListView.isCurrentItem
            onClicked: {
                listView.currentIndex = index
                stackView.push(model.source)
                drawer.close()
            }
        }

//        model:

        ScrollIndicator.vertical: ScrollIndicator { }
    }
}
