#pragma once
#include <drogon/drogon.h>
#include <drogon/orm/CoroMapper.h>
#include <drogon/utils/coroutine.h>
#include <models/Users.h>
#include <optional>

namespace messenger::repositories {

using User = drogon_model::messenger_db::Users;

class UserRepository {
public:
    static drogon::Task<std::optional<User>> getById(int id);
    static drogon::Task<std::optional<User>> getByHandle(std::string handle);
    static drogon::Task<bool> create(
        std::string handle,
        std::string display_name,
        std::string password_hash
    );

private:
    static drogon::orm::CoroMapper<User> getMapper() {
        return drogon::orm::CoroMapper<User>(drogon::app().getDbClient());
    }
};

}  // namespace messenger::repositories