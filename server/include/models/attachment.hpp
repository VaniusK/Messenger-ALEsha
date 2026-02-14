#ifndef ATTACHMENT_HPP_
#define ATTACHMENT_HPP_

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

namespace messenger::models {

struct Attachment {
    int64_t id{};

    std::optional<int64_t> message_id;
    std::string file_type;
    int64_t file_size;
    std::string file_path;
    std::chrono::system_clock::time_point uploaded_at;
};

}  // namespace messenger::models

#endif  // ATTACHMENT_HPP_