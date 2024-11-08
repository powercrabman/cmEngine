#pragma once
#include "cmScript.h"

class cmRenderer;
class cmTransform;
class cmCamera;

class DummyScript : public cmScript
{
public:
	DummyScript() = default;
	virtual ~DummyScript() = default;

	void Initialize() override;
	void OnStart() override;
	void OnFinish() override;
	void Update() override;
	void LateUpdate() override;

private:
	cmMeshRenderer* mMesh = nullptr;
	cmTransform* mTrans = nullptr;
};

