import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

ApplicationWindow {
    id: root

    width: 640
    height: 480
    visible: true
    title: directoryModel.dirName

    ColumnLayout {

        id: mainColumnLayout
        anchors.fill: parent

        RowLayout{
            TextField {
                id: directoryPathFiled
                text: directoryModel.absolutePath
                Layout.fillWidth: true

                onAccepted: {
                    openDirectory(text)
                }

                function openDirectory(path) {
                    text = path
                    directoryModel.setCurrentDir(path)
                }
            }

            Button {
                id: moveBackButton

                icon.source: "image://mimeTypeIcon/go-up"

                onClicked: {
                    var path = directoryPathFiled.text
                    var index = path.lastIndexOf("/")
                    if(index >= 0 && path.length > 1)
                    {
                        var newPath = path.substring(0, index)
                        if(newPath.length == 0) //root
                            directoryPathFiled.openDirectory("/")
                        else
                            directoryPathFiled.openDirectory(newPath)
                    }
                }

                Layout.preferredWidth: height
            }

            ButtonGroup {
                buttons: viewStyle.children
            }

            Row {
                id: viewStyle

                RadioButton {
                    id: iconViewButton
                    text: qsTr("Значки")
                    checked: true
                }

                RadioButton {
                    id: listViewButton
                    text: qsTr("Таблица")
                }

                RadioButton {
                    id: compactViewButton
                    text: qsTr("Список")
                }
            }

            Layout.fillWidth: true
        }

        DirectoryIconView {
            id: directoryIconView
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: iconViewButton.checked
            model: directoryModel

            onDirectoryClicked: {
                directoryPathFiled.openDirectory(directoryPath)
            }
        }

        DirectoryTableView {
            id: directoryTableView
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: listViewButton.checked
            model: directoryModel

            onDirectoryClicked: {
                directoryPathFiled.openDirectory(directoryPath)
            }
        }

        DirectoryListView {
            id: directoryListView
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: compactViewButton.checked
            model: directoryModel

            onDirectoryClicked: {
                directoryPathFiled.openDirectory(directoryPath)
            }
        }


        Item {
            id: bottomPanel

            Layout.fillWidth: true
            height: bottomPanelLayout.implicitHeight

            RowLayout {
                id: bottomPanelLayout
                anchors.fill: parent
                spacing: 6

                Item {
                    //spacer
                    Layout.fillWidth: true
                }

                Text {
                    id: progress

                    text: qsTr("Загрузка директории: ") + directoryPathFiled.text
                }
            }
        }
    }

    Connections {
        target: directoryModel

        function onLoadingDirectory() {
            progress.visible = true;
        }

        function onLoadDirectoryFinished() {
            progress.visible = false;
        }
    }
}
