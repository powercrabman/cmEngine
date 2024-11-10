#pragma once
#include "cmScript.h"

class cmTransform;
class cmCamera;

class CameraScript : public cmScript
{
public:
	CameraScript() = default;
	virtual ~CameraScript() = default;

	void Setup() override;

	void OnStart() override;
	void OnFinish() override;

	void Update() override;
	void FinalUpdate() override;

private:
	cmTransform* t = nullptr;
	cmCamera* cmr = nullptr;
};