#ifndef CHANNEL_HPP_
#define CHANNEL_HPP_

#include <drogon/orm/Field.h>
#include <drogon/orm/Row.h>
#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/orm_utils.hpp>

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

    static Channel fromRow(const drogon::orm::Row &row) {
        Channel object;
        object.id = row["id"].as<int64_t>();
        object.handle = row["handle"].as<std::string>();
        object.is_private = row["is_private"].as<bool>();
        object.discussion_chat_id =
            messenger::utils::fromNullable<int64_t>(row["discussion_chat_id"]);
        object.avatar_path =
            messenger::utils::fromNullable<std::string>(row["avatar_path"]);
        object.description = row["description"].as<std::string>();
        object.created_at =
            row["created_at"].as<std::chrono::system_clock::time_point>();

        return object;
    }
};

struct ChannelMember {
    int64_t channel_id{};
    int64_t user_id{};
    ChannelRole role{ChannelRole::Member};
    std::chrono::system_clock::time_point joined_at;

    static ChannelMember fromRow(const drogon::orm::Row &row) {
        ChannelMember object;
        object.channel_id = row["channel_id"].as<int64_t>();
        object.user_id = row["user_id"].as<int64_t>();
        object.role = row["role"].as<ChannelRole>();
        object.joined_at =
            row["joined_at"].as<std::chrono::system_clock::time_point>();

        return object;
    }
};

}  // namespace messenger::models

#endif  // CHANNEL_HPP_
