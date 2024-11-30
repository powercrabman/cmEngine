#include "0. cmEngine/cmEngine.h"
#include "GameEntity.h"

namespace cmEngine
{
	GameEntity GameEntity::NullEntity = GameEntity{ nullptr, entt::null };

	GameEntity::GameEntity(Scene* inScene, entt::entity inEntity)
		: mEntity(inEntity)
	{
		if (inScene) { mRegi = &inScene->GetRegistry(); }
		else { mRegi = nullptr; }
	}
}
