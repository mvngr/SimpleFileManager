#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "fileclipboard.h"
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
    FileClipboard* fileClipboard = new FileClipboard(&engine);

    QObject::connect(fileClipboard, &FileClipboard::fileAppeared, directoryModel, &DirectoryModel::checkForUpdate);
    QObject::connect(fileClipboard, &FileClipboard::fileDisappeared, directoryModel, &DirectoryModel::checkForUpdate);

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("directoryModel", directoryModel);
    context->setContextProperty("fileClipboard", fileClipboard);

    engine.addImageProvider("mimeTypeIcon", new MimeTypeIconsProvider());

    const QUrl url("qrc:/qml/main.qml");
    engine.load(url);

    return app.exec();
}
