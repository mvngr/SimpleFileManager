#include "fileclipboard.h"

#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QDir>
#include <QMimeData>
#include <QUrl>

void FileClipboard::paste(const QDir& directory)
{
    QDir dir = directory;
    const QClipboard* clipboard = QApplication::clipboard();
    const QMimeData* mimeData = clipboard->mimeData();

    if (mimeData->hasUrls()) {
        auto urls = mimeData->urls();
        for (const QUrl& url : urls) {
            dir.rename(url.toLocalFile(), url.fileName());
        }
    }
}
