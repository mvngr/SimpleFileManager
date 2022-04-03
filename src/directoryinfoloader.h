#ifndef DIRECTORYINFOLOADER_H
#define DIRECTORYINFOLOADER_H

#include <QDir>
#include <QFileInfo>
#include <QObject>

class DirectoryInfoLoader : public QObject {
    Q_OBJECT
public:
    explicit DirectoryInfoLoader(QObject* parent = nullptr);
    ~DirectoryInfoLoader();

    void setFilters(const QDir::Filters filters = QDir::NoFilter, const QDir::SortFlags sort = QDir::NoSort);
    Q_INVOKABLE void setCurrentDir(const QDir& dir);

signals:
    void directoryUpdated(const QFileInfoList& dirInfo);

protected:
    QDir directory_;
    QDir::Filters filters_ = QDir::AllEntries | QDir::NoDotAndDotDot;
    QDir::SortFlags sort_ = QDir::NoSort;
};

Q_DECLARE_METATYPE(QDir)

#endif // DIRECTORYINFOLOADER_H
