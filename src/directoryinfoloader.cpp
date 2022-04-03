#include "directoryinfoloader.h"

DirectoryInfoLoader::DirectoryInfoLoader(QObject* parent)
    : QObject(parent)
{
}

DirectoryInfoLoader::~DirectoryInfoLoader()
{
}

void DirectoryInfoLoader::setFilters(const QDir::Filters filters, const QDir::SortFlags sort)
{
    filters_ = filters;
    sort_ = sort;
}

void DirectoryInfoLoader::setCurrentDir(const QDir& dir)
{
    directory_ = dir;
    auto data = directory_.entryInfoList(filters_, sort_);
    emit directoryUpdated(data);
}
