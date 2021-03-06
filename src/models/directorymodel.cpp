#include "directorymodel.h"

#include <QApplication>
#include <QClipboard>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QFileIconProvider>
#include <QIcon>
#include <QMimeData>
#include <QMimeDatabase>
#include <QUrl>
#include <array>

DirectoryModel::DirectoryModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    loaderThread_ = new QThread(this);
    loader_ = new DirectoryInfoLoader();
    loader_->moveToThread(loaderThread_);
    connect(loaderThread_, &QThread::finished, loader_, &QObject::deleteLater);
    connect(loader_, &DirectoryInfoLoader::directoryUpdated, this, &DirectoryModel::onDirectoryUpdated, Qt::QueuedConnection);
    loaderThread_->start();
    setCurrentDir(QDir::home());
}

DirectoryModel::~DirectoryModel()
{
    loaderThread_->quit();
    loaderThread_->wait();
}

int DirectoryModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return cache_.size();
}

int DirectoryModel::columnCount(const QModelIndex& parent) const
{
    return static_cast<int>(Columns::Count);
}

QVariant DirectoryModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // чтобы не нарушать принцип DRY буду обрабатывать колонки как роли
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case Name:
            role = NameRole;
            break;
        case Type:
            role = TypeRole;
            break;
        case Size:
            role = SizeRole;
            break;
        case ModifiedDate:
            role = ModifiedDateRole;
            break;
        default:
            qWarning() << tr("Неизвестная колонка: %1").arg(index.column());
        }
    }

    switch (role) {
    case NameRole:
        return cache_[index.row()].baseName();
    case TypeRole:
        static const QMimeDatabase mimeDb;
        return mimeDb.mimeTypeForFile(cache_[index.row()]).name();
    case SizeRole: {
        static const QLocale locale;
        return locale.formattedDataSize(cache_[index.row()].size());
    }
    case ModifiedDateRole:
        return cache_[index.row()].lastModified();
    case IconRole: {
        static const QFileIconProvider provider;
        return provider.icon(cache_[index.row()]).name();
    }
    case IsDirRole:
        return cache_[index.row()].isDir();
    case AbsolutePathRole:
        return cache_[index.row()].absoluteFilePath();
    }

    return QVariant();
}

QVariant DirectoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    static const std::array<QString, 4> columns {
        tr("Название"),
        tr("Тип данных"),
        tr("Размер"),
        tr("Дата последнего изменения"),
    };

    assert(columns.size() == static_cast<std::size_t>(Columns::Count) && "Please, write headerData for column");

    return columns[section];
}

QHash<int, QByteArray> DirectoryModel::roleNames() const
{
    return {
        { Qt::DisplayRole, "display" },
        { NameRole, "name" },
        { TypeRole, "type" },
        { SizeRole, "size" },
        { ModifiedDateRole, "modifiedDate" },
        { IconRole, "icon" },
        { IsDirRole, "isDir" },
        { AbsolutePathRole, "absolutePath" },
    };
}

void DirectoryModel::setCurrentDir(const QString& path)
{
    QDir dir = QDir(path);
    if (dir.exists())
        setCurrentDir(dir);
    else
        qWarning() << tr("Неудачная попытка открыть директорию: %1").arg(path);
}

void DirectoryModel::setCurrentDir(const QDir& directory)
{
    currentDir_ = directory;
    emit loadingDirectory();
    QMetaObject::invokeMethod(loader_, "setCurrentDir", Qt::QueuedConnection, Q_ARG(QDir, directory));
}

QString DirectoryModel::absolutePath() const
{
    return currentDir_.absolutePath();
}

QString DirectoryModel::dirName() const
{
    return currentDir_.dirName();
}

void DirectoryModel::openFile(const QString& path) const
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    qInfo() << tr("Выполнен запуск: %1").arg(path);
}

void DirectoryModel::checkForUpdate(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    if (fileInfo.absolutePath() == currentDir_.path()) {
        int index = cache_.indexOf(fileInfo);
        //если файл пропал
        if (index != -1 && !QFile::exists(filePath)) {
            beginRemoveRows(QModelIndex(), index, index);
            cache_.removeAt(index);
            endRemoveRows();
        }
        //если найден новый файл
        if (index == -1 && QFile::exists(filePath)) {
            beginInsertRows(QModelIndex(), cache_.size(), cache_.size());
            cache_.push_back(fileInfo);
            endInsertRows();
        }
    }
}

void DirectoryModel::onDirectoryUpdated(const QFileInfoList& dirInfo)
{
    emit loadDirectoryFinished();
    beginResetModel();
    cache_ = dirInfo;
    endResetModel();
}
