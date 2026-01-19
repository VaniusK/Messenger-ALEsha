#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace messenger::models {

struct Session {
    int64_t id{};
    int64_t user_id{};
    std::string token_hash;
    std::chrono::system_clock::time_point created_at;
    std::chrono::system_clock::time_point expires_at;
};

} // namespace messenger::models
