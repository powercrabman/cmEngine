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

	void Setup() override;
	void OnStart() override;
	void OnFinish() override;
	void Update() override;
	void FinalUpdate() override;

private:
	cmTransform* mTrans = nullptr;
};

