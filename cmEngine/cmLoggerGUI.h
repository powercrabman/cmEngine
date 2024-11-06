#pragma once
#include "cmGUI.h"


class cmLoggerGUI : public cmGUI
{
public:
	cmLoggerGUI() = default;
	virtual ~cmLoggerGUI() = default;

	void Initialize() override;
	void RenderGUI() override;
	
	void NeedScroll() { mNeedScroll = true; }

private:
	enum LOGGER_SHOW_FLAGS
	{
		LOGGER_SHOW_FLAGS_TRACE = 1 << 0,
		LOGGER_SHOW_FLAGS_DEBUG = 1 << 1,
		LOGGER_SHOW_FLAGS_INFO = 1 << 2,
		LOGGER_SHOW_FLAGS_WARN = 1 << 3,
		LOGGER_SHOW_FLAGS_ERROR = 1 << 4,
		LOGGER_SHOW_FLAGS_FATAL = 1 << 5,

		LOGGER_SHOW_FLAGS_ALL = LOGGER_SHOW_FLAGS_TRACE |
		LOGGER_SHOW_FLAGS_DEBUG |
		LOGGER_SHOW_FLAGS_INFO |
		LOGGER_SHOW_FLAGS_WARN |
		LOGGER_SHOW_FLAGS_ERROR |
		LOGGER_SHOW_FLAGS_FATAL
	};

	ImGuiTextFilter mFilter;
	uint32 mShowFlags = LOGGER_SHOW_FLAGS_ALL;

	bool mAutoScroll = true;
	bool mNeedScroll = false;
};

