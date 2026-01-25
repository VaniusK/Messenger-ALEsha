#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

namespace messenger::models {

enum class ChannelRole { Member, Admin, Owner };

struct Channel {
    int64_t id{};
    std::string name;
    std::string handle;
    bool is_private{false};
    std::optional<int64_t> discussion_chat_id{};
    std::optional<std::string> avatar_path;
    std::string description;
    std::chrono::system_clock::time_point created_at;
};

struct ChannelMember {
    int64_t channel_id{};
    int64_t user_id{};
    ChannelRole role{ChannelRole::Member};
    std::chrono::system_clock::time_point joined_at;
};

}  // namespace messenger::models
