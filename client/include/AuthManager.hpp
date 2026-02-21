#pragma once

#include <qnetworkaccessmanager.h>
#include <qtmetamacros.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QString>

class AuthManager : public QObject {
    Q_OBJECT

public:
    explicit AuthManager(QObject *parent = nullptr);
    Q_INVOKABLE void registerUser(
        const QString &handle,
        const QString &displayName,
        const QString &password
    );
    Q_INVOKABLE void loginUser(const QString &handle, const QString &password);

signals:
    void registerSuccess();
    void registerFailed(const QString &errorMsg);

    void loginSuccess(const QString &token);
    void loginFailed(const QString &errorMsg);

private:
    QNetworkAccessManager *m_networkManager;
};
