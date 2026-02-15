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
    drogon::Task<std::optional<User>> getById(int id);
    drogon::Task<std::optional<User>> getByHandle(std::string handle);
    drogon::Task<bool> create(
        std::string handle,
        std::string display_name,
        std::string password_hash
    );

private:
    drogon::orm::CoroMapper<User> getMapper() {
        return drogon::orm::CoroMapper<User>(drogon::app().getDbClient());
    }
};

}  // namespace messenger::repositories