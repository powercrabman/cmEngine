#include "EnginePch.h"
#include "SceneManager.h"
#include "Scene.h"

namespace cmEngine
{
	void SceneManager::UpdateCore()
	{
		if (mCurrentScene)
		{
			mCurrentScene->UpdateScene();
			mCurrentScene->FinalUpdate();
			mCurrentScene->PreRender();
		}
	}
}
