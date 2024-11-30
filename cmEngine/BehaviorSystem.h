#pragma once

namespace cmEngine
{
	void BehaviorSystem(Scene* inScene)
	{
		auto view = inScene->GetView<Behavior>();
		for (auto entity : view)
		{
			view.get<Behavior>(entity).userFunction(GameEntity{ &inScene->GetRegistry(), entity });
		}
	}
}
