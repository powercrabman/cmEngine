#pragma once

#define NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_ADL_SERIALIZER(Type, ...)   \
namespace nlohmann                                                     \
{                                                                      \
    template <>                                                        \
    struct adl_serializer<Type>                \
    {                                                                  \
    static void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
    static void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__)) }\
    };                                                                 \
}    

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_ADL_SERIALIZER(ImVec4, x, y, z, w);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_ADL_SERIALIZER(Vector3, x, y, z);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_ADL_SERIALIZER(Vector4, x, y, z, w);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_ADL_SERIALIZER(Color, x, y, z, w);
