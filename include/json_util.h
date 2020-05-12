//
// Created by Alex on 2020/1/28.
//

#ifndef JSON_UTIL_H
#define JSON_UTIL_H

#include <cstddef>
#include <cstring>
#include <string>
#include <regex>
#include <codecvt>
#include "json.hpp"
#define JSON_SERIALIZE(Type, TO, FROM) \
    namespace nlohmann { \
        template <> struct adl_serializer<Type> { \
            static void to_json(json& j, const Type& value) TO \
            static void from_json(const json& j, Type& value) FROM \
        }; \
    }
using json = nlohmann::json;
static std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
namespace nlohmann {
    template <>
    struct adl_serializer<const wchar_t *> {
        static void to_json(json &j, const wchar_t *value) {
            j = conv.to_bytes(value);
        }
    };
}
JSON_SERIALIZE(std::wstring, {
    j = conv.to_bytes(value);
}, {
    value = conv.from_bytes(j);
});

#endif //JSON_UTIL_H
