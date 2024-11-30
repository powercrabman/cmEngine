#include "pch.h"
#include "OldcmLogger.h"
#include "OldcmLogGUI.h"
#include "cmRenderer.h"
#include "cmGUIRenderer.h"

OldcmLogger::OldcmLogger() = default;

void OldcmLogger::Initalize()
{
	mLogGUI = Engine.Renderer->GetGUIRenderer()->CreateGUI<OldcmLogGUI>();
}

void OldcmLogger::Logging(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	mLogGUI->Logging(format, args);
	va_end(args);
}

void OldcmLogger::Logging(eLogType type, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	mLogGUI->Logging(type, format, args);
	va_end(args);
}

