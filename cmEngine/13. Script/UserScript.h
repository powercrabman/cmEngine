#pragma once

namespace cmEngine
{
	void UserScript(Scene* inScene)
	{
		auto view = inScene->GetView<Behavior>();
		for (auto entity : view)
		{
			view.get<Behavior>(entity).userFunction(GameEntity{ inScene, entity });
		}
	}
}
