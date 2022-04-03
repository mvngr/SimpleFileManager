#ifndef DIRECTORYMODEL_H
#define DIRECTORYMODEL_H

#include "src/directoryinfoloader.h"
#include "src/fileclipboard.h"

#include <QAbstractTableModel>
#include <QFileInfoList>
#include <QThread>

#include <QFileSystemModel>

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

    enum ColumnUserRole {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        SizeRole,
        ModifiedDateRole,
        IconRole,
        IsDirRole,
        AbsolutePathRole,
        CountRole,
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

    Q_INVOKABLE void openFile(const QString& path) const;

    Q_INVOKABLE void cut(const QString& path) const;
    Q_INVOKABLE void copy(const QString& path) const;
    Q_INVOKABLE void paste(const QString& path);
    Q_INVOKABLE void remove(const QString& path) const;

signals:
    void loadingDirectory();
    void loadDirectoryFinished();

private:
    void onDirectoryUpdated(const QFileInfoList& dirInfo);

    QDir currentDir_;
    QFileInfoList cache_;
    DirectoryInfoLoader* loader_;
    QThread* loaderThread_;
};

#endif // DIRECTORYMODEL_H
