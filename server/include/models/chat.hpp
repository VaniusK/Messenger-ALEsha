#ifndef CHAT_HPP_
#define CHAT_HPP_

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

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
};

struct ChatMember {
    int64_t chat_id{};
    int64_t user_id{};
    ChatRole role{ChatRole::Member};
    std::optional<int64_t> last_read_message_id{};
    std::chrono::system_clock::time_point joined_at;
};

}  // namespace messenger::models

#endif  // CHAT_HPP_
