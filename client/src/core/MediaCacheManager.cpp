#include "MediaCacheManager.hpp"
#include <qimage.h>
#include <qnetworkrequest.h>
#include <qstandardpaths.h>
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaObject>
#include <QUrl>
#include <QWidget>
#include <cerrno>
#include "ConnectionManager.hpp"

MediaCacheManager::MediaCacheManager(
    ConnectionManager *connection,
    QObject *parent
)
    : QObject(parent), m_connection(connection) {
}

QString MediaCacheManager::getOrPut(
    const QString &s3_object_key,
    const QString &download_url
) {
    auto cache_location =
        QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

    QDir cache_dir(QDir::cleanPath(
        QDir(cache_location).path() + QDir::separator() + "media"
    ));
    if (!cache_dir.exists()) {
        cache_dir.mkdir(".");
    }
    QDir file_location(QDir::cleanPath(
        QDir(cache_dir).path() + QDir::separator() + s3_object_key
    ));

    if (file_location.exists()) {
        return file_location.path();
    }

    file = new QFile(file_location.path());

    if (!file->open(QIODevice::WriteOnly)) {
        qDebug() << "Couldn't open file";
        return "";
    }

    QNetworkRequest request(download_url);
    reply = m_connection->networkManager()->get(request);
    connect(
        reply, &QNetworkReply::finished, this, &MediaCacheManager::onFinished
    );
    return file_location.path();
}

void MediaCacheManager::onFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        file->write(reply->readAll());
        qDebug() << "Saved file";
    } else {
        qDebug() << "Error while saving file:" << reply->errorString();
    }

    file->close();
    file->deleteLater();
    reply->deleteLater();
}
