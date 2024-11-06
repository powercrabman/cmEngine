#pragma once
#include "cmGUI.h"

class cmGUI;

class cmPopupGUI : public cmGUI
{
public:
	cmPopupGUI() = default;
	virtual ~cmPopupGUI() = default;

	void Initialize() override;
	void RenderGUI() override;

private:
	// Cache
	cmGUI* mLog     = nullptr;
	cmGUI* mDebug   = nullptr;
	cmGUI* mConsole = nullptr;
};

