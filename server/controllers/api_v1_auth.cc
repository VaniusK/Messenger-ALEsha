#include "api_v1_auth.h"

using namespace api::v1;

Task<HttpResponsePtr> auth::registerUser(HttpRequestPtr req){
    // UserRepository repo;
    // some logic with co_await
    Json::Value ret;
    ret["status"] = "ok";
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    co_return resp;
}

Task<HttpResponsePtr> auth::loginUser(HttpRequestPtr req){
    // UserRepository repo;
    // some logic with co_await
    Json::Value ret;
    ret["status"] = "ok";
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    co_return resp;
}
