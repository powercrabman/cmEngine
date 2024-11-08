#pragma once

#define ENGINE_MODULE_BODY()	\
friend class cmEngine;			\
friend class cmApplication;

#define RESOURCE_BODY()			\
friend class cmResourceManager;			

#define LOG_TRACE(format, ...)	Engine->GetLogger()->Logging(eLogLevel::Trace,format, __VA_ARGS__)
#define LOG_INFO(format, ...)	Engine->GetLogger()->Logging(eLogLevel::Info,format, __VA_ARGS__)
#define LOG_WARN(format, ...)	Engine->GetLogger()->Logging(eLogLevel::Warn,format, __VA_ARGS__)
#define LOG_ERROR(format, ...)	Engine->GetLogger()->Logging(eLogLevel::Error,format, __VA_ARGS__)
#define LOG_FATAL(format, ...)	Engine->GetLogger()->Logging(eLogLevel::Fatal,format, __VA_ARGS__)

#if defined(_DEBUG) || defined(DEBUG)
#define LOG_DEBUG(format, ...) Engine->GetLogger()->Logging(eLogLevel::Debug, format, __VA_ARGS__)
#else
#define LOG_DEBUG(format, ...) (void)0
#endif

#define FILL_ZERO(Destination, Type) memset((Destination),0,(sizeof(Destination))

#define TYPE_ID(type)			cmTypeIDGen<type>::ID()

#define INTERFACE class

#define KEY_PRESS(KeyCode)		Engine->GetKeyboard()->IsPressed(KeyCode)
#define KEY_RELEASE(KeyCode)	Engine->GetKeyboard()->IsRelease(KeyCode)
#define KEY_AWAY(KeyCode)		Engine->GetKeyboard()->IsAway(KeyCode)
#define KEY_HOLD(KeyCode)		Engine->GetKeyboard()->IsHold(KeyCode)

#define DELTA_TIME				Engine->GetTimer()->GetDeltaTime()