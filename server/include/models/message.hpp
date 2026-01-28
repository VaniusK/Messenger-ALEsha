#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

namespace messenger::models {

struct Message {
    int64_t id{};
    int64_t chat_id{};
    std::optional<int64_t> sender_id;               // NULL if user deleted
    std::optional<int64_t> reply_to_message_id;     // NULL if not a reply
    std::optional<int64_t> forwarded_from_user_id;  // NULL if not forwarded
    std::optional<std::string>
        forwarded_from_user_name;  // NULL if not forwarded
    std::string text;
    std::chrono::system_clock::time_point sent_at;
    std::optional<std::chrono::system_clock::time_point>
        edited_at;  // NULL if not edited
};

}  // namespace messenger::models

#endif  // MESSAGE_HPP_
