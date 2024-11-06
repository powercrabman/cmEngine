#pragma once
#include "cmScene.h"

class DummyScene : public cmScene
{
public:
	DummyScene() = default;
	virtual ~DummyScene() = default;

	void EnterScene() override;
	void ExitScene() override;
};

