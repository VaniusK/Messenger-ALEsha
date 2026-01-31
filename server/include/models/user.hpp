#ifndef USER_HPP_
#define USER_HPP_

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

namespace messenger::models {

struct User {
    int64_t id{};
    std::string handle;        // unique, e.g. "john_doe"
    std::string display_name;  // shown in UI, e.g. "John Doe"
    std::string password_hash;
    std::optional<std::string> avatar_path;
    int64_t last_synced_message_id{0};
    int64_t last_synced_post_id{0};
    std::string description;
    std::chrono::system_clock::time_point created_at;
};

}  // namespace messenger::models

#endif  // USER_HPP_
