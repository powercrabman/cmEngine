#include "EnginePch.h"
#include "NewGameEntity.h"

namespace cmEngine
{
	NewGameEntity::NewGameEntity(entt::entity inEntity)
		: mEntity(inEntity)
	{
		mRegistry = &SceneManager::GetCurrentScene()->GetRegistry();
	}
}
