#ifndef USER_HPP_
#define USER_HPP_

#include <drogon/orm/Field.h>
#include <drogon/orm/Row.h>
#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/orm_utils.hpp>

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

    static User fromRow(const drogon::orm::Row &row) {
        User object;
        object.id = row["id"].as<int64_t>();
        object.handle = row["handle"].as<std::string>();
        object.display_name = row["display_name"].as<std::string>();
        object.password_hash = row["password_hash"].as<std::string>();
        object.avatar_path =
            messenger::utils::fromNullable<std::string>(row["avatar_path"]);
        object.last_synced_message_id =
            row["last_synced_message_id"].as<int64_t>();
        object.last_synced_post_id = row["last_synced_post_id"].as<int64_t>();
        object.description = row["description"].as<std::string>();
        object.created_at =
            row["created_at"].as<std::chrono::system_clock::time_point>();

        return object;
    }
};

}  // namespace messenger::models

#endif  // USER_HPP_
