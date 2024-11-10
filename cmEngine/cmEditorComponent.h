#pragma once
#include "cmComponent.h"
#include "cmISetupable.h"

//////////////////////////////
// 해당 기능은 Debug 모드
// 에서만 동작함
//////////////////////////////

class cmGUI;

class cmEditorComponent
	: public		cmComponent
	, IMPLEMENTS	cmISetupable
{
public:
	cmEditorComponent() = default;
	virtual ~cmEditorComponent() = default;

	void Setup() override;

	void OnStart() override;
	void OnFinish() override;

private:
	std::function<void(void)> mLayout = nullptr;
	cmGUI* mGui = nullptr;
};

