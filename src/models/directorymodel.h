#ifndef DIRECTORYMODEL_H
#define DIRECTORYMODEL_H

#include "src/directoryinfoloader.h"
#include "src/fileclipboard.h"

#include <QAbstractTableModel>
#include <QFileInfoList>
#include <QThread>

///
/// \brief Модель директории
///
/// Асинхронно получает данные об указанной в setCurrentDir директории
///
class DirectoryModel : public QAbstractTableModel {
    Q_OBJECT
    Q_PROPERTY(QString absolutePath READ absolutePath NOTIFY loadingDirectory)
    Q_PROPERTY(QString dirName READ dirName NOTIFY loadingDirectory)
public:
    /// \brief Столбцы модели
    enum Columns {
        Name = 0, ///< Название
        Type, ///< Тип данных
        Size, ///< Размер
        ModifiedDate, ///< Дата последнего изменения
        Count, ///< Количество столбцов (используется для облегчения кода)
    };

    /// \brief Дополнительные роли модели
    ///
    /// Используются в QML элементах
    enum ColumnUserRole {
        NameRole = Qt::UserRole + 1, ///< Название
        TypeRole, ///< Тип данных
        SizeRole, ///< Размер
        ModifiedDateRole, ///< Дата последнего изменения
        IconRole, ///< Путь до иконки файла (иконка берется из mime типа файла)
        IsDirRole, ///< Является ли строка директорией
        AbsolutePathRole, ///< Абсолютный путь до директории/файла
        CountRole, ///< Количество столбцов (используется для облегчения кода)
    };

    explicit DirectoryModel(QObject* parent = nullptr);
    ~DirectoryModel();

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setCurrentDir(const QString& path);
    Q_INVOKABLE void setCurrentDir(const QDir& directory);

    QString absolutePath() const;
    QString dirName() const;

    /// \brief Выполяет открытие файла системной программой
    /// \param path файл, который нужно открыть
    Q_INVOKABLE void openFile(const QString& path) const;

    /// \brief Проверяет, существует ли файл и правит кэшированные данные
    /// \param filePath путь до файла, который появился/исчез
    ///
    /// \todo Перевести на QFileSystemWatcher
    void checkForUpdate(const QString& filePath);
signals:
    /// \brief Начата асинхронная загрузка директории
    void loadingDirectory();
    /// \brief Завершена асинхронная загрузка директории
    void loadDirectoryFinished();

private:
    /// \brief Применяет асинхронно полученные данные о директории
    void onDirectoryUpdated(const QFileInfoList& dirInfo);

    QDir currentDir_;
    QFileInfoList cache_;
    DirectoryInfoLoader* loader_; ///< Асинхронный загрузчик информации о директории
    QThread* loaderThread_;
};

#endif // DIRECTORYMODEL_H
