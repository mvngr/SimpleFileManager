import QtQuick 2.0
import QtQuick.Controls 2.15

Menu {
    id: menu

    property string targetAbsolutePath: ""

    Action {
        text: qsTr("Вырезать")
        icon.source: "image://mimeTypeIcon/edit-cut"
        onTriggered: {
            fileClipboard.cut([targetAbsolutePath])
        }
    }
    Action {
        text: qsTr("Копировать")
        icon.source: "image://mimeTypeIcon/edit-copy"
        onTriggered: {
            fileClipboard.copy([targetAbsolutePath])
        }
    }
    Action {
        text: qsTr("Вставить")
        icon.source: "image://mimeTypeIcon/edit-paste"
        onTriggered: {
            fileClipboard.paste(targetAbsolutePath)
        }
    }
    Action {
        text: qsTr("Удалить")
        icon.source: "image://mimeTypeIcon/edit-delete"
        onTriggered: {
            fileClipboard.remove([targetAbsolutePath])
        }
    }
}
