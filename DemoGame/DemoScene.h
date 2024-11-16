#pragma once

class DemoScene : public cmEngine::Scene
{
public:
	SCENE_BODY(DemoScene);

	void EnterScene() override;
	void ExitScene() override;
};

