#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

namespace messenger::models {

struct Reaction {
    int64_t id{};

    // XOR
    std::optional<int64_t> message_id;
    std::optional<int64_t> post_id;
    int64_t user_id;
    std::string emoji;
    std::chrono::system_clock::time_point reacted_at;
};

}  // namespace messenger::models
