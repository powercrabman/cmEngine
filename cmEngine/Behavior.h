#pragma once

namespace cmEngine
{
	struct Behavior
	{
		std::function<void(GameEntity inEntity)> userFunction = nullptr;
	};
}
