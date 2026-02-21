#include "StateManager.hpp"
#include <qobject.h>
#include <qstringliteral.h>

StateManager::StateManager(QObject *parent) : QObject(parent) {
    m_token = "";
    m_currentUserHandle = "";
}

QString StateManager::getToken() const {
    return m_token;
}

void StateManager::setToken(const QString &token) {
    if (m_token != token) {
        m_token = token;
        emit tokenChanged();
    }
}

QString StateManager::getCurrentUserHandle() const {
    return m_currentUserHandle;
}

void StateManager::setCurrentUserHandle(const QString &handle) {
    if (m_currentUserHandle != handle) {
        m_currentUserHandle = handle;
        emit currentUserHandleChanged();
    }
}

bool StateManager::isLoggedIn() const {
    return !m_token.isEmpty();
}

void StateManager::clearState() {
    setToken("");
    setCurrentUserHandle("");
}