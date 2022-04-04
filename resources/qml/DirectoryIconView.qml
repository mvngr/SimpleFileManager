import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtQuick.Controls 2.15

Item {
    id: iconView

    property alias model: gridView.model
    signal directoryClicked(string directoryPath)

    GridView {
        id: gridView

        anchors.fill: parent
        clip: true

        cellWidth: 64
        cellHeight: 64 + textIcon.implicitHeight

        Component {
            id: objectDelegate
            Item {
                id: objectItem

                width: gridView.cellWidth
                height: gridView.cellHeight

                Image {
                    id: imageIcon
                    source: "image://mimeTypeIcon/" + icon
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: gridView.cellWidth
                    sourceSize.height: gridView.cellWidth
                    anchors{
                        top: parent.top
                        left: parent.left
                        right: parent.right
                        bottom: textIcon.top
                    }

                    FileContextMenu {
                        id: fileContextMenu
                        visible: false
                    }

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        onClicked: {
                            gridView.currentIndex = index
                            if(mouse.button & Qt.RightButton)
                            {
                                fileContextMenu.targetAbsolutePath = absolutePath
                                fileContextMenu.visible = true
                                fileContextMenu.x = mouseX
                                fileContextMenu.y = mouseY
                            }
                        }

                        onDoubleClicked: {
                            if(mouse.button & Qt.LeftButton) {
                                if(isDir)
                                {
                                    gridView.currentIndex = -1
                                    directoryClicked(absolutePath)
                                }
                                else
                                {
                                    gridView.model.openFile(absolutePath)
                                }
                            }
                        }
                    }
                }

                Text {
                    id: textIcon
                    text: name
                    horizontalAlignment: Text.AlignHCenter
                    height: font.pixelSize * 2.5
                    wrapMode: Text.Wrap
                    anchors {
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                    }

                    clip: true
                }

                ToolTip
                {
                    text: name
                    visible: objectItemArea.containsMouse && text
                    delay: Qt.styleHints.mousePressAndHoldInterval

                }
                MouseArea {
                    id: objectItemArea
                    anchors.fill: parent
                    hoverEnabled: true
                    propagateComposedEvents: true
                }

            }
        }
        delegate: objectDelegate

        highlightMoveDuration: 0
        highlight: Rectangle {
            color: "blue"
            opacity: 0.1
            z: 2
        }
    }
}
