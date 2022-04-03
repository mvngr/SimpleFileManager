#ifndef MIMETYPEICONSPROVIDER_H
#define MIMETYPEICONSPROVIDER_H

#include <QQuickImageProvider>

class MimeTypeIconsProvider : public QQuickImageProvider {
public:
    MimeTypeIconsProvider();

    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override;
};

#endif // MIMETYPEICONSPROVIDER_H
