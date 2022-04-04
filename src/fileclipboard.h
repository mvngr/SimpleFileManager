#ifndef FILECLIPBOARD_H
#define FILECLIPBOARD_H

#include <QClipboard>
#include <QDir>

///
/// \brief Вспомогательный класс для работы с буфером обмена
///
/// При помощи данного класса можно копировать/вырезать/вставить файлы,
/// а так же удалить их
///
class FileClipboard : public QObject {
    Q_OBJECT
public:
    FileClipboard(QObject* parent = nullptr);

    Q_INVOKABLE void cut(const QList<QString>& filePaths) const;
    Q_INVOKABLE void copy(const QList<QString>& filePaths) const;
    Q_INVOKABLE void paste(const QString& directoryPath) const;
    Q_INVOKABLE void remove(const QList<QString>& filePaths) const;

    /// \brief название кастомного майм типа перемещения
    static const QString cuttedMime;

    /// \brief название кастомного майм типа для копирования
    static const QString copiedMime;

signals:
    /// \brief Файл пропал из директории
    /// \param filePath Пропавший файл
    void fileDisappeared(const QString& filePath) const;

    /// \brief fileAppeared Файл появился в директории
    /// \param filePath Появившийся файл
    void fileAppeared(const QString& filePath) const;

private:
    /// \brief Вспомогательный метод для вставки в буфер обмена нового значения
    /// \param mimeType Задаваемый майм тип
    /// \param filePaths Пути до файлов
    void addToClipboard(const QString& mimeType, const QList<QString>& filePaths) const;

    /// \brief Вспомогательный метод для преобразования QByteArray в список QUrl
    /// \param byteArray исходные данные
    /// \return Список ссылок
    QList<QUrl> urlsFromByteArray(const QByteArray& byteArray) const;

    QClipboard* clipboard = nullptr;
};

#endif // FILECLIPBOARD_H
