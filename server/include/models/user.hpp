#pragma once

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
    std::string description;
    std::chrono::system_clock::time_point created_at;
};

}  // namespace messenger::models
