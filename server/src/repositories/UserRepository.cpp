#include <drogon/orm/Criteria.h>
#include "repositories/UserRepository.hpp"
#include <stdexcept>

using User = drogon_model::messenger_db::Users;
using UserRepository = messenger::repositories::UserRepository;

using namespace drogon;
using namespace drogon::orm;

Task<std::optional<User>> UserRepository::getById(int id) {
    CoroMapper<User> mapper = getMapper();

    try {
        User user = co_await mapper.findByPrimaryKey(id);

        co_return user;
    } catch (const UnexpectedRows &e) {
        co_return std::nullopt;
    } catch (const DrogonDbException &e) {
        throw std::runtime_error("Database error");
    }
}

Task<std::optional<User>> UserRepository::getByHandle(std::string handle) {
    CoroMapper<User> mapper = getMapper();

    try {
        User user = co_await mapper.findOne(
            Criteria(User::Cols::_handle, CompareOperator::EQ, handle)
        );

        co_return user;
    } catch (const UnexpectedRows &e) {
        co_return std::nullopt;
    } catch (const DrogonDbException &e) {
        throw std::runtime_error("Database error");
    }
}

Task<std::vector<User>> UserRepository::getAll() {
    CoroMapper<User> mapper = getMapper();

    try {
        std::vector<User> users = co_await mapper.findAll();

        co_return users;
    } catch (const DrogonDbException &e) {
        throw std::runtime_error("Database error");
    }
}

Task<bool> UserRepository::create(
    std::string handle,
    std::string display_name,
    std::string password_hash
) {
    CoroMapper<User> mapper = getMapper();

    try {
        User user;
        user.setHandle(handle);
        user.setDisplayName(display_name);
        user.setPasswordHash(password_hash);
        co_await mapper.insert(user);
        co_return true;
    } catch (const DrogonDbException &e) {
        // assuming it means UNIQUE constraint violation
        // idk how to distinguish it from generic db exeption
        co_return false;
    }
}