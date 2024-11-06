#pragma once
#include "cmGUI.h"
#include "cmConsoleData.h"

class cmConsoleGUI : public cmGUI
{
public:
	cmConsoleGUI();
	virtual ~cmConsoleGUI() = default;

	void Initialize() override;
	void RenderGUI() override;

	void ClearHistory() { mHistory.clear(); }
	void SendConsoleData(std::string_view inMsg, eConsoleDataType isCoreMsg = eConsoleDataType::Normal);

private:
	void CommandHandler();

private:
	cmStaticTextBuffer<256>  mInputBuffer;

	//Log 에 보이는 커맨드 메시지
	std::vector<std::string> mHistory;
	int32 mHistroyIndex = -1;
	bool mAutoScroll = true;
	bool mNeedScroll = true;
};