#include "mimetypeiconsprovider.h"

#include <QStyle>

MimeTypeIconsProvider::MimeTypeIconsProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

QPixmap MimeTypeIconsProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    QSize curSize = requestedSize.isValid() ? requestedSize : QSize(128, 128);
    QPixmap pixmap = QIcon::fromTheme(id).pixmap(curSize);
    *size = pixmap.size();
    return pixmap;
}
