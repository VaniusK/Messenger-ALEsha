#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QSignalSpy>
#include <memory>
#include "AuthManager.hpp"
#include "StateManager.hpp"
#include "mocks/FakeNetworkReply.hpp"
#include "mocks/MockConnectionManager.hpp"

using ::testing::_;
using ::testing::Return;

class AuthManagerTest : public ::testing::Test {
protected:
    std::unique_ptr<QCoreApplication> app;
    std::shared_ptr<MockConnectionManager> mockConn;
    std::unique_ptr<StateManager> stateManager;
    std::unique_ptr<AuthManager> authManager;

    void SetUp() override {
        if (!QCoreApplication::instance()) {
            static int argc = 1;
            static char name[] = "test";
            static char *argv[] = {name, nullptr};
            app = std::make_unique<QCoreApplication>(argc, argv);
        }

        mockConn = std::make_shared<MockConnectionManager>();
        stateManager = std::make_unique<StateManager>();
        authManager =
            std::make_unique<AuthManager>(mockConn.get(), stateManager.get());
    }
};

TEST_F(AuthManagerTest, RegisterSuccess) {
    auto *fakeReply = new FakeNetworkReply(201, "{}");
    EXPECT_CALL(*mockConn, post(QString("/auth/register"), _))
        .WillOnce(Return(fakeReply));

    QSignalSpy spy(authManager.get(), &AuthManager::registerSuccess);

    authManager->registerUser("alyosha", "Alesha", "pass");
    fakeReply->emitFinished();
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(AuthManagerTest, RegisterConflictFail) {
    auto *fakeReply = new FakeNetworkReply(409, "{}");
    EXPECT_CALL(*mockConn, post(QString("/auth/register"), _))
        .WillOnce(Return(fakeReply));

    QSignalSpy spy(authManager.get(), &AuthManager::registerFailed);

    authManager->registerUser("alyosha", "Alesha", "pass");
    fakeReply->emitFinished();
    EXPECT_EQ(spy.count(), 1);
    QString errorMsg = spy.takeFirst().at(0).toString();
    EXPECT_EQ(errorMsg, "Пользователь с таким логином уже существует");
}

TEST_F(AuthManagerTest, LoginSuccessSetsToken) {
    auto *fakeReply = new FakeNetworkReply(200, "{\"token\":\"mega_token\"}");
    EXPECT_CALL(*mockConn, post(QString("/auth/login"), _))
        .WillOnce(Return(fakeReply));

    auto *fakeIdReply = new FakeNetworkReply(200, "{\"id\":99}");
    EXPECT_CALL(*mockConn, get(QString("/users/handle/alyosha")))
        .WillOnce(Return(fakeIdReply));

    QSignalSpy loginSpy(authManager.get(), &AuthManager::loginSuccess);

    authManager->loginUser("alyosha", "pass");
    fakeReply->emitFinished();
    fakeIdReply->emitFinished();
    EXPECT_EQ(loginSpy.count(), 1);
    EXPECT_EQ(stateManager->getToken(), "mega_token");
    EXPECT_EQ(stateManager->getUserId(), 99);
}
