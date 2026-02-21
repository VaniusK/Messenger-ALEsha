#pragma once

#include <qobject.h>
#include <qqmlintegration.h>
#include <qtmetamacros.h>
#include <QObject>
#include <QString>

class StateManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString token READ getToken WRITE setToken NOTIFY tokenChanged)
    Q_PROPERTY(QString currentUserHandle READ getCurrentUserHandle WRITE
                   setCurrentUserHandle NOTIFY currentUserHandleChanged)

public:
    explicit StateManager(QObject *parent = nullptr);

    QString getToken() const;
    void setToken(const QString &token);

    QString getCurrentUserHandle() const;
    void setCurrentUserHandle(const QString &handle);

    Q_INVOKABLE bool isLoggedIn() const;
    Q_INVOKABLE void clearState();

signals:
    void tokenChanged();
    void currentUserHandleChanged();

private:
    QString m_token;
    QString m_currentUserHandle;
};