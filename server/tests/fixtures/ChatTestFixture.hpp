#pragma once
#include "DbTestFixture.hpp"
#include "repositories/ChatRepository.hpp"
#include "repositories/UserRepository.hpp"

using ChatRepository = messenger::repositories::ChatRepository;
using UserRepository = messenger::repositories::UserRepository;
using User = messenger::repositories::User;

class ChatTestFixture : public DbTestFixture {
private:
    UserRepository user_repo_ = UserRepository();

protected:
    ChatRepository repo_ = ChatRepository();
    User dummy_user1_;
    User dummy_user2_;

public:
    void SetUp() override {
        auto dbClient = app().getDbClient();
        dbClient->execSqlSync("SET client_min_messages TO WARNING;");
        dbClient->execSqlSync("TRUNCATE TABLE users CASCADE;");
        drogon::sync_wait(
            user_repo_.create("dummy_user1", "dummy_user1", "hash")
        );
        dummy_user1_ =
            drogon::sync_wait(user_repo_.getByHandle("dummy_user1")).value();
        drogon::sync_wait(
            user_repo_.create("dummy_user2", "dummy_user2", "hash")
        );
        dummy_user2_ =
            drogon::sync_wait(user_repo_.getByHandle("dummy_user2")).value();
    }
};