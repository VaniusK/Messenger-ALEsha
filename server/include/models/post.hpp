#ifndef POST_HPP_
#define POST_HPP_

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

namespace messenger::models {

struct Post {
    int64_t id{};
    int64_t channel_id;
    std::optional<int64_t> discussion_message_id;  // NULL for disabled comments
    std::string text;
    std::chrono::system_clock::time_point posted_at;
    std::optional<std::chrono::system_clock::time_point>
        edited_at;  // NULL if not edited
};

}  // namespace messenger::models

#endif  // POST_HPP_
