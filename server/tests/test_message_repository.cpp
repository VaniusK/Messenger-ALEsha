#include <drogon/orm/Result.h>
#include "fixtures/MessageTestFixture.hpp"

using MessageRepository = messenger::repositories::MessageRepository;
using Message = drogon_model::messenger_db::Messages;

using namespace drogon;
using namespace drogon::orm;

TEST_F(MessageTestFixture, TestSend) {
    /* When valid data is provided
    send() should create a new message,
    and it should be retrievable via getAll()*/
    Message message = sync_wait(repo_.send(
        dummy_chat_.getValueOfId(), dummy_user1_.getValueOfId(), "my message",
        std::nullopt, std::nullopt
    ));
    std::vector<Message> messages = sync_wait(repo_.getAll());
    EXPECT_EQ(messages.size(), 1);
    EXPECT_EQ(messages[0].getValueOfId(), message.getValueOfId());
}

TEST_F(MessageTestFixture, TestSendOptionals) {
    /* When valid data with optional arguments is provided
    send() should create a new message,
    and it should be retrievable via getAll()*/
    Message original_message = sync_wait(repo_.send(
        dummy_chat_.getValueOfId(), dummy_user1_.getValueOfId(), "my message",
        std::nullopt, std::nullopt
    ));
    Message message = sync_wait(repo_.send(
        dummy_chat_.getValueOfId(), dummy_user1_.getValueOfId(), "my message",
        original_message.getValueOfId(), dummy_user2_.getValueOfId()
    ));
    std::vector<Message> messages = sync_wait(repo_.getAll());
    EXPECT_EQ(messages.size(), 2);
}

TEST_F(MessageTestFixture, TestSendMultiple) {
    /* When multiple messages are sent,
    send() should create a new message for each,
    and they should be retrievable via getAll()*/
    Message message1 = sync_wait(repo_.send(
        dummy_chat_.getValueOfId(), dummy_user1_.getValueOfId(), "my message",
        std::nullopt, std::nullopt
    ));
    Message message2 = sync_wait(repo_.send(
        dummy_chat_.getValueOfId(), dummy_user1_.getValueOfId(), "my message",
        std::nullopt, std::nullopt
    ));
    Message message3 = sync_wait(repo_.send(
        dummy_chat_.getValueOfId(), dummy_user1_.getValueOfId(), "my message",
        std::nullopt, std::nullopt
    ));
    std::vector<Message> messages = sync_wait(repo_.getAll());
    EXPECT_EQ(messages.size(), 3);
}

TEST_F(MessageTestFixture, TestGetById) {
    /* When message with given id exists
    getById() should return in*/
    Message message = sync_wait(repo_.send(
        dummy_chat_.getValueOfId(), dummy_user1_.getValueOfId(), "my message",
        std::nullopt, std::nullopt
    ));
    auto result = sync_wait(repo_.getById(message.getValueOfId()));
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value().getValueOfId(), message.getValueOfId());
}

TEST_F(MessageTestFixture, TestGetByIdFail) {
    /* When message with given id does not exist
    getById() should return nullopt*/
    Message message = sync_wait(repo_.send(
        dummy_chat_.getValueOfId(), dummy_user1_.getValueOfId(), "my message",
        std::nullopt, std::nullopt
    ));
    auto result = sync_wait(repo_.getById(message.getValueOfId() + 1));
    EXPECT_FALSE(result.has_value());
}