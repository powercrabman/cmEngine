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