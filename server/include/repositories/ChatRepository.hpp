#pragma once
#include <drogon/drogon.h>
#include <drogon/orm/CoroMapper.h>
#include <drogon/utils/coroutine.h>
#include "models/ChatMembers.h"
#include "models/Chats.h"

namespace messenger::repositories {

using Chat = drogon_model::messenger_db::Chats;
using ChatMember = drogon_model::messenger_db::ChatMembers;

class ChatRepositoryInterface {
public:
    virtual ~ChatRepositoryInterface() = default;
    virtual drogon::Task<Chat>
    getOrCreateDirect(int64_t user1_id, int64_t user2_id) = 0;
};

class ChatRepository : public ChatRepositoryInterface {
public:
    drogon::Task<Chat> getOrCreateDirect(int64_t user1_id, int64_t user2_id)
        override;

private:
    drogon::orm::CoroMapper<Chat> getMapper() {
        return drogon::orm::CoroMapper<Chat>(drogon::app().getDbClient());
    }

    drogon::orm::CoroMapper<ChatMember> getChatMemberMapper() {
        return drogon::orm::CoroMapper<ChatMember>(drogon::app().getDbClient());
    }
};

}  // namespace messenger::repositories