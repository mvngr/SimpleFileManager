#ifndef MIMETYPEICONSPROVIDER_H
#define MIMETYPEICONSPROVIDER_H

#include <QQuickImageProvider>

///
/// \brief Провайдер изображений, полученных из системы для майм типов
///
class MimeTypeIconsProvider : public QQuickImageProvider {
public:
    MimeTypeIconsProvider();

    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override;
};

#endif // MIMETYPEICONSPROVIDER_H
