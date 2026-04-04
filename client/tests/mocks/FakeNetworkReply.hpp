#pragma once
#include <qnetworkreply.h>
#include <QByteArray>
#include <QNetworkReply>
#include <algorithm>

class FakeNetworkReply : public QNetworkReply {
    Q_OBJECT
public:
    FakeNetworkReply(
        int statusCode,
        const QByteArray &responceBody,
        QObject *parent = nullptr
    )
        : QNetworkReply(parent), m_data(responceBody) {
        setAttribute(QNetworkRequest::HttpStatusCodeAttribute, statusCode);
        open(QIODeviceBase::ReadOnly);
        setError(QNetworkReply::NoError, "");
    }

    void emitFinished() {
        emit finished();
    }

protected:
    qint64 readData(char *data, qint64 maxlen) override {
        qint64 len = std::min(maxlen, (qint64)m_data.size());
        memcpy(data, m_data.constData(), len);
        m_data.remove(0, len);
        return len;
    }

    void abort() override {
    }

    qint64 bytesAvailable() const override {
        return m_data.size() + QNetworkReply::bytesAvailable();
    }

    bool isSequential() const override {
        return true;
    }

private:
    QByteArray m_data;
};
