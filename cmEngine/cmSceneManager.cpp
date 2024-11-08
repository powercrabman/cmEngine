#include "pch.h"
#include "cmSceneManager.h"
#include "cmScene.h"

void cmSceneManager::UpdateCore()
{
	if (mCurrentScene)
	{
		mCurrentScene->UpdateScene();
		mCurrentScene->LateUpdate();
		mCurrentScene->PreRender();
	}
}
