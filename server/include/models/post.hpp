#ifndef POST_HPP_
#define POST_HPP_

#include <drogon/orm/Field.h>
#include <drogon/orm/Row.h>
#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/orm_utils.hpp>

namespace messenger::models {

struct Post {
    int64_t id{};
    int64_t channel_id;
    std::optional<int64_t> discussion_message_id;  // NULL for disabled comments
    std::string text;
    std::chrono::system_clock::time_point posted_at;
    std::optional<std::chrono::system_clock::time_point>
        edited_at;  // NULL if not edited

    static Post fromRow(const drogon::orm::Row &row) {
        Post object;
        object.id = row["id"].as<int64_t>();
        object.channel_id = row["channel_id"].as<int64_t>();
        object.discussion_message_id =
            messenger::utils::fromNullable<int64_t>(row["discussion_message_id"]
            );
        object.text = row["text"].as<std::string>();
        object.posted_at =
            row["posted_at"].as<std::chrono::system_clock::time_point>();
        object.edited_at = messenger::utils::fromNullable<
            std::chrono::system_clock::time_point>(row["edited_at"]);

        return object;
    }
};

}  // namespace messenger::models

#endif  // POST_HPP_
