#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "mimetypeiconsprovider.h"
#include "models/directorymodel.h"

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    QQuickStyle::setStyle("Fusion");
    QQmlApplicationEngine engine;

    DirectoryModel* directoryModel = new DirectoryModel(&engine);
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("directoryModel", directoryModel);

    engine.addImageProvider("mimeTypeIcon", new MimeTypeIconsProvider());

    const QUrl url("qrc:/qml/main.qml");
    engine.load(url);

    return app.exec();
}
