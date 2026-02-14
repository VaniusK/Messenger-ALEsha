#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <drogon/orm/Field.h>
#include <drogon/orm/Row.h>
#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/orm_utils.hpp>

namespace messenger::models {

struct Message {
    int64_t id{};
    int64_t chat_id{};
    std::optional<int64_t> sender_id;               // NULL if user deleted
    std::optional<int64_t> reply_to_message_id;     // NULL if not a reply
    std::optional<int64_t> forwarded_from_user_id;  // NULL if not forwarded
    std::optional<std::string>
        forwarded_from_user_name;  // NULL if not forwarded
    std::string text;
    std::chrono::system_clock::time_point sent_at;
    std::optional<std::chrono::system_clock::time_point>
        edited_at;  // NULL if not edited

    static Message fromRow(const drogon::orm::Row &row) {
        Message object;
        object.id = row["id"].as<int64_t>();
        object.chat_id = row["chat_id"].as<int64_t>();
        object.sender_id =
            messenger::utils::fromNullable<int64_t>(row["sender_id"]);
        object.reply_to_message_id =
            messenger::utils::fromNullable<int64_t>(row["reply_to_message_id"]);
        object.forwarded_from_user_id = messenger::utils::fromNullable<int64_t>(
            row["forwarded_from_user_id"]
        );
        object.forwarded_from_user_name =
            messenger::utils::fromNullable<std::string>(
                row["forwarded_from_user_name"]
            );
        object.text = row["text"].as<std::string>();
        object.sent_at =
            row["sent_at"].as<std::chrono::system_clock::time_point>();
        object.edited_at = messenger::utils::fromNullable<
            std::chrono::system_clock::time_point>(row["edited_at"]);

        return object;
    }
};

}  // namespace messenger::models

#endif  // MESSAGE_HPP_
