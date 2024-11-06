#pragma once

class OldcmLogGUI;

class OldcmLogger
{
	ENGINE_MODULE_BODY();
public:
	virtual ~OldcmLogger() = default;

	void Initalize();

	void Logging(const char* format, ...);
	void Logging(eLogType type, const char* format, ...);

private:
	OldcmLogger();

private:
	OldcmLogGUI* mLogGUI = nullptr;
};