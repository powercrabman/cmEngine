#pragma once
#include "cmScript.h"

class cmTransform;
class cmCamera;

class CameraScript : public cmScript
{
public:
	CameraScript() = default;

	void Initialize() override;

	void OnStart() override;
	void OnFinish() override;

	void Update() override;
	void LateUpdate() override;

private:
	cmTransform* t = nullptr;
	cmCamera* cmr = nullptr;
};