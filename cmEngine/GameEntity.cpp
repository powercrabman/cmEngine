#include "EnginePch.h"
#include "GameEntity.h"
#include "SceneManager.h"
#include "Scene.h"

namespace cmEngine
{
	GameEntity GameEntity::NullEntity = GameEntity{ nullptr, entt::null };

	GameEntity::GameEntity(entt::entity inEntity)
		: mEntity(inEntity)
	{
		mRegi = &SceneManager::GetCurrentScene()->GetRegistry();
	}
}
