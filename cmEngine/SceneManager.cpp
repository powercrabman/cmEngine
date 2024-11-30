#include "EnginePch.h"
#include "SceneManager.h"
#include "Scene.h"

namespace cmEngine
{
	void SceneManager::Update()
	{
		if (mCurrentScene)
		{
			mCurrentScene->UpdateScene();
		}
	}
	void SceneManager::Render()
	{
		if (mCurrentScene)
		{
			mCurrentScene->RenderScene();
		}
	}
}
