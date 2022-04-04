#ifndef FILECLIPBOARD_H
#define FILECLIPBOARD_H

#include <QClipboard>
#include <QDir>

class FileClipboard : public QObject {
    Q_OBJECT
public:
    FileClipboard(QObject* parent = nullptr);

    Q_INVOKABLE void cut(const QList<QString>& filePaths) const;
    Q_INVOKABLE void copy(const QList<QString>& filePaths) const;
    Q_INVOKABLE void paste(const QString& directoryPath) const;
    Q_INVOKABLE void remove(const QList<QString>& filePaths) const;

    static const QString cuttedMime;
    static const QString copiedMime;

signals:
    void fileDisappeared(const QString& filePath) const;
    void fileAppeared(const QString& filePath) const;

private:
    void addToClipboard(const QString& mimeType, const QList<QString>& filePaths) const;
    QList<QUrl> urlsFromByteArray(const QByteArray& byteArray) const;

    QClipboard* clipboard = nullptr;
};

#endif // FILECLIPBOARD_H
