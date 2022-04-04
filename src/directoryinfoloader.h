#ifndef DIRECTORYINFOLOADER_H
#define DIRECTORYINFOLOADER_H

#include <QDir>
#include <QFileInfo>
#include <QObject>

///
/// \brief Загрузчик информации о директории
///
/// Запускается в отдельном потоке из DirectoryModel
/// для получения информации о содержимом директории
///
class DirectoryInfoLoader : public QObject {
    Q_OBJECT
public:
    explicit DirectoryInfoLoader(QObject* parent = nullptr);
    ~DirectoryInfoLoader();

    /// \brief Задать фильтры для директории (аналог QDir::setNameFilters)
    /// \param filters Параметры фильтрации
    /// \param sort Параметры сортировки
    void setFilters(const QDir::Filters filters = QDir::NoFilter, const QDir::SortFlags sort = QDir::NoSort);
    Q_INVOKABLE void setCurrentDir(const QDir& dir);

signals:
    /// \brief Новые данные загружены
    /// \param dirInfo новые данные о директории
    void directoryUpdated(const QFileInfoList& dirInfo);

protected:
    QDir directory_;
    QDir::Filters filters_ = QDir::AllEntries | QDir::NoDotAndDotDot;
    QDir::SortFlags sort_ = QDir::NoSort;
};

Q_DECLARE_METATYPE(QDir)

#endif // DIRECTORYINFOLOADER_H
