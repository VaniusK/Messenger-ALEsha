#ifndef SESSION_HPP_
#define SESSION_HPP_

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

}  // namespace messenger::models

#endif  // SESSION_HPP_
