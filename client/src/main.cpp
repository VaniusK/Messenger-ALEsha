// Messenger Client Entry Point

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/messenger_client_uri/src/main.qml"_qs);
    engine.load(url);
    return app.exec();
}
