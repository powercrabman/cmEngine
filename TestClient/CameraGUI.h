#pragma once
#include "cmGUI.h"

class cmCamera;

class CameraGUI : public cmGUI
{
public:
	CameraGUI() {};
	virtual ~CameraGUI() {};

	void Initialize() override;
	void RenderGUI() override;

	void SetCameraObject(cmCamera* inCmr)
	{
		mCmr = inCmr;
	}

private:
	cmCamera* mCmr = nullptr;
};

