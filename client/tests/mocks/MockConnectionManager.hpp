#pragma once
#include <gmock/gmock.h>
#include <QNetworkReply>
#include "ConnectionManager.hpp"

class MockConnectionManager : public ConnectionManager {
public:
    MockConnectionManager() : ConnectionManager([]() { return QString(""); }) {
    }

    MOCK_METHOD(QNetworkReply *, get, (const QString &endpoint), (override));
    MOCK_METHOD(
        QNetworkReply *,
        post,
        (const QString &endpoint, const QByteArray &body),
        (override)
    );
    MOCK_METHOD(
        QNetworkReply *,
        getWithBody,
        (const QString &endpoint, const QByteArray &body),
        (override)
    );
};