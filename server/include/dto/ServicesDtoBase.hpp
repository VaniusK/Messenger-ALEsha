#pragma once
#include <json/value.h>

namespace messenger::dto {

struct ResponseDto {
    virtual Json::Value toJson() = 0;
};

struct RequestDto {};

}  // namespace messenger::dto
