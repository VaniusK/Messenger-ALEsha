#ifndef CHAT_HPP_
#define CHAT_HPP_

#include <drogon/orm/Field.h>
#include <drogon/orm/Row.h>
#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/orm_utils.hpp>

namespace messenger::models {

enum class ChatRole { Member, Moderator, Admin, Owner };
enum class ChatType { Direct, Group, Discussion, Saved };

struct Chat {
    int64_t id{};
    std::optional<std::string> name;  // NULL for direct chats
    ChatType type;
    std::optional<std::string> avatar_path;
    std::string description;
    std::optional<int64_t> direct_user1_id;
    std::optional<int64_t> direct_user2_id;
    std::chrono::system_clock::time_point created_at;

    static Chat fromRow(const drogon::orm::Row &row) {
        Chat object;
        object.id = row["id"].as<int64_t>();
        object.name = messenger::utils::fromNullable<std::string>(row["name"]);
        object.type = row["type"].as<ChatType>();
        object.direct_user1_id =
            messenger::utils::fromNullable<int64_t>(row["direct_user1_id"]);
        object.direct_user2_id =
            messenger::utils::fromNullable<int64_t>(row["direct_user2_id"]);
        object.created_at =
            row["created_at"].as<std::chrono::system_clock::time_point>();

        return object;
    }
};

struct ChatMember {
    int64_t chat_id{};
    int64_t user_id{};
    ChatRole role{ChatRole::Member};
    std::optional<int64_t> last_read_message_id{};
    std::chrono::system_clock::time_point joined_at;

    static ChatMember fromRow(const drogon::orm::Row &row) {
        ChatMember object;
        object.chat_id = row["chat_id"].as<int64_t>();
        object.user_id = row["user_id"].as<int64_t>();
        object.role = row["role"].as<ChatRole>();
        object.last_read_message_id =
            messenger::utils::fromNullable<int64_t>(row["last_read_message_id"]
            );
        object.joined_at =
            row["joined_at"].as<std::chrono::system_clock::time_point>();

        return object;
    }
};

}  // namespace messenger::models

#endif  // CHAT_HPP_
