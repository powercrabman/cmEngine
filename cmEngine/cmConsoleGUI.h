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

	//Log �� ���̴� Ŀ�ǵ� �޽���
	std::vector<std::string> mHistory;
	int32 mHistroyIndex = -1;
	bool mAutoScroll = true;
	bool mNeedScroll = true;
};