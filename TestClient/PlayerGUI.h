#pragma once
#include "cmGUI.h"

class cmGameObject;
class cmTransform;
class cmMeshRenderer;

class PlayerGUI : public cmGUI
{
public:
	PlayerGUI() = default;
	virtual ~PlayerGUI() = default;

	void Initialize() override;
	void RenderGUI() override;

	void SetEntity(cmGameObject* inObj);

private:
	cmGameObject* mObj = nullptr;
	cmTransform* t = nullptr;
	cmMeshRenderer* r = nullptr;
};

