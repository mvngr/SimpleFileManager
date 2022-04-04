#include "fileclipboard.h"

#include <QApplication>
#include <QClipboard>
#include <QDataStream>
#include <QDebug>
#include <QMimeData>
#include <QUrl>

const QString FileClipboard::cuttedMime = "simple-file-manager/cutted-files";
const QString FileClipboard::copiedMime = "simple-file-manager/copied-files";

FileClipboard::FileClipboard(QObject* parent)
    : QObject(parent)
    , clipboard(QApplication::clipboard())
{
}

void FileClipboard::cut(const QList<QString>& filePaths) const
{
    addToClipboard(cuttedMime, filePaths);
}

void FileClipboard::copy(const QList<QString>& filePaths) const
{
    addToClipboard(copiedMime, filePaths);
}

void FileClipboard::paste(const QString& directoryPath) const
{
    const QMimeData* mimeData = clipboard->mimeData();

    QFileInfo info = QFileInfo(directoryPath);
    QDir dir = QDir(info.absolutePath());
    if (mimeData->hasFormat(cuttedMime)) {
        const QList<QUrl> urls = urlsFromByteArray(mimeData->data(cuttedMime));

        for (const QUrl& url : qAsConst(urls)) {
            QString newPath = dir.absoluteFilePath(url.fileName());
            qInfo() << tr("Перемещаю файл \"%1\" в \"%2\"").arg(url.toLocalFile(), newPath);
            dir.rename(url.toLocalFile(), url.fileName());
            emit fileDisappeared(url.toLocalFile());
            emit fileAppeared(newPath);
        }
    } else {
        if (mimeData->hasFormat(copiedMime)) {
            const QList<QUrl> urls = urlsFromByteArray(mimeData->data(copiedMime));

            for (const QUrl& url : qAsConst(urls)) {
                QString newPath = dir.absoluteFilePath(url.fileName());
                qInfo() << tr("Копирую файл \"%1\" в \"%2\"").arg(url.toLocalFile(), newPath);
                QFile::copy(url.toLocalFile(), newPath);
                emit fileAppeared(newPath);
            }
        }
    }
}

void FileClipboard::remove(const QList<QString>& filePaths) const
{
    for (const auto& path : filePaths) {
        QFile::moveToTrash(path);
        qInfo() << tr("Удаляю файл: \"%1\"").arg(path);
        emit fileDisappeared(path);
    }
}

void FileClipboard::addToClipboard(const QString& mimeType, const QList<QString>& filePaths) const
{
    QMimeData* mimeData = new QMimeData();

    QList<QUrl> data;
    data.reserve(filePaths.size());
    for (const auto& path : filePaths) {
        data.append(QUrl::fromLocalFile(path));
    }

    QByteArray ba;
    QDataStream ds(&ba, QIODevice::WriteOnly);
    ds << data;

    mimeData->setData(mimeType, ba);
    clipboard->setMimeData(mimeData);
}

QList<QUrl> FileClipboard::urlsFromByteArray(const QByteArray& byteArray) const
{
    QList<QUrl> urls;
    QDataStream ds(byteArray);
    ds >> urls;

    return urls;
}
