#pragma once
#include "cmGUI.h"

// ���߿� �ʿ�� ����׸� ���� ���� ���� ���

class cmDebugGUI : public cmGUI
{
public:
	cmDebugGUI() = default;
	virtual ~cmDebugGUI() = default;

	void Initialize() override;
	void RenderGUI() override;

private:
	ImGuiWindowFlags mMoveFlag = ImGuiWindowFlags_NoMove;

	float mWindowAlpha         = 0.7f;
	ImVec2 mScreenPosToAdjust  = { 0, 0 };
	bool mNeedWindowPosAdjust  = false;

	const char* mWindowName = "DebugGUI";
};
