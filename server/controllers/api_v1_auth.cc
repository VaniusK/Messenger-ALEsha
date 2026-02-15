#include "api_v1_auth.h"
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <drogon/drogon_callbacks.h>
#include <json/value.h>
#include <optional>
#include "crypto/bcrypt.h"
#include "models/Users.h"
#include "repositories/UserRepository.hpp"

using namespace api::v1;
using namespace messenger::repositories;

Task<HttpResponsePtr> auth::registerUser(HttpRequestPtr req) {
    UserRepository repo;
    using User = drogon_model::messenger_db::Users;
    auto req_json = req->getJsonObject();

    Json::Value response_json;
    std::vector<std::string> unfinded_fields;
    const std::vector<std::string> required_fields = {
        "handle", "password", "display_name"
    };
    for (const auto &required_field : required_fields) {
        if (!(*req_json).isMember(required_field)) {
            unfinded_fields.push_back(required_field);
        }
    }
    if (!unfinded_fields.empty()) {
        std::string missing_fields_str = "Missing fields: ";
        for (const auto &field : unfinded_fields) {
            missing_fields_str += field;
            if (field != unfinded_fields.back()) {
                missing_fields_str += ", ";
            }
        }
        response_json["message"] =
            "Invalid JSON: couldn't find some fields. " + missing_fields_str;
        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(response_json);
        resp->setStatusCode(drogon::k400BadRequest);
        co_return resp;
    }
    std::optional<User> user = co_await repo.getByHandle(
        std::string((*req_json)["handle"].asString())
    );
    if (user == std::nullopt) {
        std::string password_hash =
            bcrypt::generateHash((*req_json)["password"].asString());
        bool success = co_await repo.create(
            std::string((*req_json)["handle"].asCString()),
            std::string((*req_json)["display_name"].asCString()), password_hash
        );
        if (success) {
            response_json["message"] = "New user was successfully created";
            response_json["password_hash"] = password_hash;
            HttpResponsePtr resp =
                HttpResponse::newHttpJsonResponse(response_json);
            resp->setStatusCode(drogon::k201Created);
            co_return resp;
        } else {
            response_json["message"] =
                "Internal server error: user wasn't created";
            HttpResponsePtr resp =
                HttpResponse::newHttpJsonResponse(response_json);
            resp->setStatusCode(drogon::k500InternalServerError);
            co_return resp;
        }
    } else {
        response_json["message"] = "User already exists";
        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(response_json);
        resp->setStatusCode(drogon::k409Conflict);
        co_return resp;
    }
}

Task<HttpResponsePtr> auth::loginUser(HttpRequestPtr req) {
    UserRepository repo;
    using User = drogon_model::messenger_db::Users;
    auto req_json = req->getJsonObject();
    Json::Value response_json;
    const std::vector<std::string> required_fields = {"handle", "password"};
    std::vector<std::string> unfinded_fields;
    for (const auto &required_field : required_fields) {
        if (!(*req_json).isMember(required_field)) {
            unfinded_fields.push_back(required_field);
        }
    }
    if (!unfinded_fields.empty()) {
        std::string missing_fields_str = "Missing fields: ";
        for (const auto &field : unfinded_fields) {
            missing_fields_str += field;
            if (field != unfinded_fields.back()) {
                missing_fields_str += ", ";
            }
        }
        response_json["message"] =
            "Invalid JSON: couldn't find some fields. " + missing_fields_str;
        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(response_json);
        resp->setStatusCode(drogon::k400BadRequest);
        co_return resp;
    }
    std::optional<User> user = co_await repo.getByHandle(
        std::string((*req_json)["handle"].asCString())
    );
    if (user == std::nullopt) {
        response_json["message"] = "Login error: Invalid handle or password";
        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(response_json);
        resp->setStatusCode(drogon::k401Unauthorized);
        co_return resp;
    } else {
        if (!bcrypt::validatePassword(
                std::string((*req_json)["password"].asCString()),
                user->getValueOfPasswordHash()
            )) {
            response_json["message"] =
                "Login error: Invalid handle or password";
            HttpResponsePtr resp =
                HttpResponse::newHttpJsonResponse(response_json);
            resp->setStatusCode(drogon::k401Unauthorized);
            co_return resp;
        }
        response_json["message"] = "Login successful";
        HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(response_json);
        resp->setStatusCode(drogon::k200OK);
        co_return resp;
    }
}
