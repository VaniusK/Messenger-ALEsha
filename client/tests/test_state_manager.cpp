#include <gtest/gtest.h>
#include <memory>
#include "StateManager.hpp"

class StateManagerTest : public ::testing::Test {
protected:
    std::unique_ptr<StateManager> stateManager;

    void SetUp() override {
        stateManager = std::make_unique<StateManager>();
    }
};

TEST_F(StateManagerTest, InitialStateIsClean) {
    EXPECT_EQ(stateManager->getUserId(), -1);
    EXPECT_EQ(stateManager->getToken(), "");
    EXPECT_EQ(stateManager->getCurrentUserHandle(), "");
    EXPECT_FALSE(stateManager->isLoggedIn());
}

TEST_F(StateManagerTest, LoginAndSetStateWorks) {
    stateManager->setUserId(42);
    stateManager->setToken("cool_jwt");
    stateManager->setCurrentUserHandle("alyosha");

    EXPECT_EQ(stateManager->getUserId(), 42);
    EXPECT_EQ(stateManager->getToken(), "cool_jwt");
    EXPECT_EQ(stateManager->getCurrentUserHandle(), "alyosha");
    EXPECT_TRUE(stateManager->isLoggedIn());
}

TEST_F(StateManagerTest, ClearStateWorks) {
    stateManager->setToken("meow");
    stateManager->setUserId(52);
    stateManager->clearState();

    EXPECT_EQ(stateManager->getToken(), "");
    EXPECT_EQ(stateManager->getUserId(), -1);
    EXPECT_FALSE(stateManager->isLoggedIn());
}
