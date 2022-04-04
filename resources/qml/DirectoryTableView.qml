import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: directoryTable

    property alias model: tableView.model
    signal directoryClicked(string directoryPath)

    HorizontalHeaderView {
        id: horizontalHeader
        syncView: tableView
        anchors.left: tableView.left

        clip: true
        delegate: Rectangle {
            implicitHeight: headerCell.implicitHeight
            Text {
                id: headerCell
                text: display
                anchors.fill: parent
                padding: 5
                clip: true
            }
            color: "#e0e0e0"
            clip: true

            Rectangle {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                width: 2
                color: "#efefef"

                MouseArea {
                    id: columnSizeArea
                    property int clickPos: 0

                    onPressed: {
                        clickPos  = mouse.x
                    }

                    onPositionChanged: {
                        var delta = mouse.x-clickPos.x
                        tableView.columnsSize[index] += delta
                        tableView.forceLayout()
                    }
                }
            }
        }
    }

    TableView {
        // грустно дела с TableView обстоят :(

        id: tableView

        property var columnsSize: [200, 100, 100]
        boundsBehavior : Flickable.StopAtBounds

        anchors {
            top: horizontalHeader.bottom
            left: directoryTable.left
            right: directoryTable.right
            bottom: directoryTable.bottom
        }

        columnWidthProvider: function(column) {
            return columnsSize[column]
        }

        Component {
            id: tableViewDelegate
            Rectangle {
                implicitWidth: 150
                implicitHeight: cellText.height

                border.width: 0

                Text {
                    id: cellText
                    text: display
                    padding: 3
                    anchors.left: parent.left
                    clip: true
                }
                clip: true

                FileContextMenu {
                    id: fileContextMenu
                    visible: false
                }

                MouseArea {
                    anchors.fill: parent

                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: {
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
                                directoryClicked(absolutePath)
                            }
                            else
                            {
                                tableView.model.openFile(absolutePath)
                            }
                        }
                    }
                }
            }
        }

        delegate: tableViewDelegate

        clip: true
    }

    onWidthChanged: {
        //Задаем размеры таблице
        var lastColumn = directoryTable.width;
        for(var i = 0; i < 3; i++)
        {
            lastColumn -= tableView.columnsSize[i];
        }
        tableView.columnsSize[3] = lastColumn
        tableView.forceLayout()
    }
}
