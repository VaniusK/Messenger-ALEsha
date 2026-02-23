#pragma once
#include "DbTestFixture.hpp"
#include "repositories/ChatRepository.hpp"
#include "repositories/MessageRepository.hpp"
#include "repositories/UserRepository.hpp"

using MessageRepository = messenger::repositories::MessageRepository;
using ChatRepository = messenger::repositories::ChatRepository;
using UserRepository = messenger::repositories::UserRepository;
using User = messenger::repositories::User;
using Chat = messenger::repositories::Chat;

class MessageTestFixture : public DbTestFixture {
private:
    ChatRepository chat_repo_;

protected:
    MessageRepository repo_ = MessageRepository();
    UserRepository user_repo_ = UserRepository();
    User dummy_user1_;
    User dummy_user2_;
    Chat dummy_chat_;

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

        dummy_chat_ = sync_wait(chat_repo_.getOrCreateDirect(
            dummy_user1_.getValueOfId(), dummy_user2_.getValueOfId()
        ));
    }
};