#pragma once

#define ENGINE_MODULE_BODY()	\
friend class cmEngine;			\
friend class cmApplication;

#define FILL_ZERO(Destination, Type) memset((&Destination),0,(sizeof(Destination)))

#define TYPE_ID(type)			cmEngine::TypeIDGen<type>::ID()

#define IMPLEMENTS	public
#undef	INTERFACE
#define INTERFACE class 

#define NODISCARD		[[nodiscard]]
#define FORCEINLINE		__forceinline

#define ENGINE_LOG_INFO(inFormat, ...)		cmEngine::Log::LogEngine(eLogLevel::Info, std::format(inFormat, __VA_ARGS__))
#define ENGINE_LOG_TRACE(inFormat, ...)		cmEngine::Log::LogEngine(eLogLevel::Trace, std::format(inFormat, __VA_ARGS__))
#define ENGINE_LOG_WARN(inFormat, ...)		cmEngine::Log::LogEngine(eLogLevel::Warn, std::format(inFormat, __VA_ARGS__))
#define ENGINE_LOG_ERROR(inFormat, ...)		cmEngine::Log::LogEngine(eLogLevel::Error, std::format(inFormat, __VA_ARGS__))
#define ENGINE_LOG_FATAL(inFormat, ...)		cmEngine::Log::LogEngine(eLogLevel::Fatal, std::format(inFormat, __VA_ARGS__))

#define LOG_INFO(inFormat, ...)				cmEngine::Log::LogClient(eLogLevel::Info, std::format(inFormat, __VA_ARGS__))
#define LOG_TRACE(inFormat, ...)			cmEngine::Log::LogClient(eLogLevel::Trace, std::format(inFormat, __VA_ARGS__))
#define LOG_WARN(inFormat, ...)				cmEngine::Log::LogClient(eLogLevel::Warn, std::format(inFormat, __VA_ARGS__))
#define LOG_ERROR(inFormat, ...)			cmEngine::Log::LogClient(eLogLevel::Error, std::format(inFormat, __VA_ARGS__))
#define LOG_FATAL(inFormat, ...)			cmEngine::Log::LogClient(eLogLevel::Fatal, std::format(inFormat, __VA_ARGS__))

#if defined(_DEBUG) || defined(DEBUG)		
#define ENGINE_LOG_DEBUG(inFormat, ...)		cmEngine::Log::LogEngine(eLogLevel::Debug, std::format(inFormat, __VA_ARGS__))
#define LOG_DEBUG(inFormat, ...)			cmEngine::Log::LogClient(eLogLevel::Debug, std::format(inFormat, __VA_ARGS__))
#else
#define ENGINE_LOG_DEBUG(inFormat, ...)
#define LOG_DEBUG(inFormat, ...)	
#endif

#define BIT(x) (1 << x)
#define BIND_FUNCTION_CALLBACK(function) [this]() { function(); }

//===================================================
//                   Json Macro
//===================================================

#define JSON_DATA_TYPE_NON_INTRUSIVE_ADL_SERIALIZER(Type, ...)   \
namespace nlohmann                                                     \
{                                                                      \
    template <>                                                        \
    struct adl_serializer<Type>                \
    {                                                                  \
    static void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
    static void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__)) }\
    };                                                                 \
}

JSON_DATA_TYPE_NON_INTRUSIVE_ADL_SERIALIZER(ImVec4, x, y, z, w);
JSON_DATA_TYPE_NON_INTRUSIVE_ADL_SERIALIZER(Vector3, x, y, z);
JSON_DATA_TYPE_NON_INTRUSIVE_ADL_SERIALIZER(Vector4, x, y, z, w);
JSON_DATA_TYPE_NON_INTRUSIVE_ADL_SERIALIZER(Color, x, y, z, w);