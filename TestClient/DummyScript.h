#pragma once
#include "cmScript.h"

class cmRenderer;

class DummyScript : public cmScript
{
public:
	DummyScript() = default;
	virtual ~DummyScript() = default;

	void Initialize() override;
	void OnStart() override;
	void OnFinish() override;
	void Update() override;
	void FinalUpdate() override;

private:
	cmMeshRenderer* mesh = nullptr;
};

