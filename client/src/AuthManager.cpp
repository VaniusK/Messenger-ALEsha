#include "AuthManager.hpp"
#include <qglobal.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qstringview.h>
#include <qurl.h>
#include <qvariant.h>
#include <QJsonDocument>
#include <QJsonObject>

AuthManager::AuthManager(QObject *parent) : QObject(parent) {
    m_networkManager = new QNetworkAccessManager(this);
}

void AuthManager::registerUser(
    const QString &handle,
    const QString &displayName,
    const QString &password
) {
    QJsonObject json;
    json["handle"] = handle;
    json["display_name"] = displayName;
    json["password"] = password;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QUrl url("http://127.0.0.1:5555/api/v1/auth/register");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_networkManager->post(request, data);
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            emit registerFailed("Network Error: " + reply->errorString());
            return;
        }

        int statusCode =
            reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if (statusCode == 201) {
            emit registerSuccess();
        } else {
            emit registerFailed("Server Error: " + QString::number(statusCode));
        }
    });
}

void AuthManager::loginUser(const QString &handle, const QString &password) {
    QJsonObject json;
    json["handle"] = handle;
    json["password"] = password;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QUrl url("http://127.0.0.1:5555/api/v1/auth/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_networkManager->post(request, data);
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            emit loginFailed("Network Error: " + reply->errorString());
            return;
        }

        int statusCode =
            reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        QByteArray responseData = reply->readAll();
        if (statusCode == 200) {
            QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
            QJsonObject responseObj = responseDoc.object();
            QString token = responseObj["access_token"].toString();

            if (token.isEmpty() &&
                responseObj["message"].toString() == "Login successful") {
                token = "dummy_token_while_server_is_wip";
            }

            if (token.isEmpty()) {
                emit loginFailed(
                    "Error: Server didn't return an access token."
                );
            } else {
                emit loginSuccess(token);
            }
        } else {
            emit loginFailed("Login Failed: " + QString::number(statusCode));
        }
    });
}
