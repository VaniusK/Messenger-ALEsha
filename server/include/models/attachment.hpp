#ifndef ATTACHMENT_HPP_
#define ATTACHMENT_HPP_

#include <drogon/orm/Field.h>
#include <drogon/orm/Row.h>
#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/orm_utils.hpp>

namespace messenger::models {

struct Attachment {
    int64_t id{};

    // XOR
    std::optional<int64_t> message_id;
    std::optional<int64_t> post_id;
    std::string file_type;
    int64_t file_size;
    std::string file_path;
    std::chrono::system_clock::time_point uploaded_at;

    static Attachment fromRow(const drogon::orm::Row &row) {
        Attachment object;
        object.id = row["id"].as<int64_t>();
        object.message_id =
            messenger::utils::fromNullable<int64_t>(row["message_id"]);
        object.post_id =
            messenger::utils::fromNullable<int64_t>(row["post_id"]);
        object.file_type = row["file_type"].as<std::string>();
        object.file_size = row["file_size"].as<int64_t>();
        object.file_path = row["file_path"].as<std::string>();
        object.uploaded_at =
            row["uploaded_at"].as<std::chrono::system_clock::time_point>();

        return object;
    }
};

}  // namespace messenger::models

#endif  // ATTACHMENT_HPP_