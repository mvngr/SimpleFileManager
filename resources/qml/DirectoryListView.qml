import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: listTable

    property alias model: listView.model
    signal directoryClicked(string directoryPath)

    ListView {

        id: listView

        anchors.fill: parent

        Component {
            id: listViewDelegate
            Rectangle {
                implicitWidth: listView.contentItem.width
                implicitHeight: cellText.height

                border.width: 0

                Image {
                    id: cellImage
                    source: "image://mimeTypeIcon/" + icon
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    height: cellText.height
                    sourceSize.width: 16
                    sourceSize.height: 16
                    fillMode: Image.PreserveAspectFit
                }

                Text {
                    id: cellText
                    text: display
                    padding: 6
                    anchors.left: cellImage.right
                    clip: true
                }

                clip: true

                MouseArea {
                    anchors.fill: parent
                    propagateComposedEvents: true
                    onClicked: {
                    listView.currentIndex = index
                   }
                    onDoubleClicked: {
                        if(isDir)
                        {
                            directoryClicked(absolutePath)
                        }
                        else
                        {
                            listView.model.openFile(absolutePath)
                        }
                    }
                }
            }
        }

        delegate: listViewDelegate

        highlightMoveDuration: 0
        highlight: Rectangle {
            color: "blue"
            opacity: 0.1
            z: 2
        }
        clip: true
    }

    onWidthChanged: {
        listView.forceLayout()
    }
}
