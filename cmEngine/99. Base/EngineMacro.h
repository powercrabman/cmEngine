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

#define ENGINE_LOG_INFO(inFormat, ...)		cmEngine::Log::Ref().LogEngine(eLogLevel::Info, std::format(inFormat, __VA_ARGS__))
#define ENGINE_LOG_TRACE(inFormat, ...)		cmEngine::Log::Ref().LogEngine(eLogLevel::Trace, std::format(inFormat, __VA_ARGS__))
#define ENGINE_LOG_WARN(inFormat, ...)		cmEngine::Log::Ref().LogEngine(eLogLevel::Warn, std::format(inFormat, __VA_ARGS__))
#define ENGINE_LOG_ERROR(inFormat, ...)		cmEngine::Log::Ref().LogEngine(eLogLevel::Error, std::format(inFormat, __VA_ARGS__))
#define ENGINE_LOG_FATAL(inFormat, ...)		cmEngine::Log::Ref().LogEngine(eLogLevel::Fatal, std::format(inFormat, __VA_ARGS__))

#define LOG_INFO(inFormat, ...)				cmEngine::Log::Ref().LogClient(eLogLevel::Info, std::format(inFormat, __VA_ARGS__))
#define LOG_TRACE(inFormat, ...)			cmEngine::Log::Ref().LogClient(eLogLevel::Trace, std::format(inFormat, __VA_ARGS__))
#define LOG_WARN(inFormat, ...)				cmEngine::Log::Ref().LogClient(eLogLevel::Warn, std::format(inFormat, __VA_ARGS__))
#define LOG_ERROR(inFormat, ...)			cmEngine::Log::Ref().LogClient(eLogLevel::Error, std::format(inFormat, __VA_ARGS__))
#define LOG_FATAL(inFormat, ...)			cmEngine::Log::Ref().LogClient(eLogLevel::Fatal, std::format(inFormat, __VA_ARGS__))

#if defined(_DEBUG) || defined(DEBUG)		
#define ENGINE_LOG_DEBUG(inFormat, ...)		cmEngine::Log::Ref().LogEngine(eLogLevel::Debug, std::format(inFormat, __VA_ARGS__))
#define LOG_DEBUG(inFormat, ...)			cmEngine::Log::Ref().LogClient(eLogLevel::Debug, std::format(inFormat, __VA_ARGS__))
#else
#define ENGINE_LOG_DEBUG(inFormat, ...)
#define LOG_DEBUG(inFormat, ...)	
#endif

#define BIT(x) (1 << x)
#define BIND_FUNCTION_CALLBACK(function) [this]() { function(); }

#define SINGLETON(ClassName)\
	friend class EngineCore;\
	private:\
	inline static ClassName* sInstance = nullptr;\
	static void Destroy()\
	{\
		if (sInstance != nullptr)\
		{\
			delete sInstance;\
			sInstance = nullptr;\
		}\
	}\
	ClassName(const ClassName&) = delete;        \
	ClassName& operator=(const ClassName&) = delete;\
	public:\
	static ClassName& Ref()\
	{\
	if (sInstance == nullptr)\
	{\
	sInstance = new ClassName(); \
	}\
	return *sInstance; \
	}\
	private:

#define TO_STRING(name)\
const char* ToString() const { return #name; }\
inline static const char* sClassName = #name

#define JSON_SERIALIZER			JsonSerializer::Ref()
#define ENGINE_CORE				EngineCore::Ref()
#define SCENE_MANAGER			SceneManager::Ref()
#define TIMER					Timer::Ref()
#define RENDERER				Renderer::Ref()
#define GUI_RENDERER			GuiRenderer::Ref()
#define EVENT_DISPATCHER		EventDispatcher::Ref()
#define COMPONENT_SERIALIZER	ComponentSerializer::Ref()
#define ASSET_MANAGER			AssetManager::Ref()