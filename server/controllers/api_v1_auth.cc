#include "api_v1_auth.h"
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <drogon/drogon_callbacks.h>
#include <json/value.h>
#include <optional>
#include <jwt-cpp/jwt.h>
#include <chrono>
#include <bcrypt/BCrypt.hpp>
#include "models/Users.h"
#include "repositories/UserRepository.hpp"
#include "utils/controller_utils.hpp"
#include "utils/server_response_macro.hpp"

using namespace api::v1;
using namespace messenger::repositories;

Task<HttpResponsePtr> auth::registerUser(HttpRequestPtr req) {
    UserRepository user_repo;
    using User = drogon_model::messenger_db::Users;
    auto req_json = req->getJsonObject();

    Json::Value response_json;
    if (utils::find_missed_fields(response_json, req_json, {"handle", "password", "display_name"})) {
        RETURN_RESPONSE_CODE_400(response_json)
    }
    std::optional<User> user =
        co_await user_repo.getByHandle((*req_json)["handle"].asString());
    if (user == std::nullopt) {
        std::string password_hash =
            BCrypt::generateHash((*req_json)["password"].asString());
        bool success = co_await user_repo.create(
            (*req_json)["handle"].asCString(),
            (*req_json)["display_name"].asCString(), password_hash
        );
        if (success) {
            response_json["message"] = "New user was successfully created";
            response_json["password_hash"] = password_hash;
            RETURN_RESPONSE_CODE_201(response_json)
        } else {
            response_json["message"] =
                "Internal server error: user wasn't created";
            RETURN_RESPONSE_CODE_500(response_json)
        }
    } else {
        response_json["message"] = "User already exists";
        RETURN_RESPONSE_CODE_409(response_json)
    }
}

Task<HttpResponsePtr> auth::loginUser(HttpRequestPtr req) {
    UserRepository repo;
    using User = drogon_model::messenger_db::Users;
    auto req_json = req->getJsonObject();
    Json::Value response_json;
    if (utils::find_missed_fields(response_json, req_json, {"handle", "password"})) {
        RETURN_RESPONSE_CODE_400(response_json)
    }
    std::optional<User> user = co_await repo.getByHandle(
        (*req_json)["handle"].asCString()
    );
    if (user == std::nullopt) {
        response_json["message"] = "Login error: Invalid handle or password";
        RETURN_RESPONSE_CODE_401(response_json)
    } else {
        if (!BCrypt::validatePassword(
                std::string((*req_json)["password"].asCString()),
                user->getValueOfPasswordHash()
            )) {
            response_json["message"] =
                "Login error: Invalid handle or password";
            RETURN_RESPONSE_CODE_401(response_json)
        }
        response_json["message"] = "Login successful";
        RETURN_RESPONSE_CODE_200(response_json)
    }
}
