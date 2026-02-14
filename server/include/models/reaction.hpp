#ifndef REACTION_HPP_
#define REACTION_HPP_

#include <drogon/orm/Field.h>
#include <drogon/orm/Row.h>
#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/orm_utils.hpp>

namespace messenger::models {

struct Reaction {
    int64_t id{};

    // XOR
    std::optional<int64_t> message_id;
    std::optional<int64_t> post_id;
    int64_t user_id;
    std::string emoji;
    std::chrono::system_clock::time_point reacted_at;

    static Reaction fromRow(const drogon::orm::Row &row) {
        Reaction object;
        object.message_id =
            messenger::utils::fromNullable<int64_t>(row["message_id"]);
        object.post_id =
            messenger::utils::fromNullable<int64_t>(row["post_id"]);
        object.user_id = row["user_id"].as<int64_t>();
        object.emoji = row["emoji"].as<std::string>();
        object.reacted_at =
            row["reacted_at"].as<std::chrono::system_clock::time_point>();

        return object;
    }
};

}  // namespace messenger::models

#endif  // REACTION_HPP_
