#include "pch.h"
#include "cmSceneManager.h"
#include "cmScene.h"

void cmSceneManager::Update()
{
	if (mCurrentScene)
	{
		mCurrentScene->UpdateScene();
	}
}

void cmSceneManager::LateUpdate()
{
	if (mCurrentScene)
	{
		mCurrentScene->LateUpdate();
	}
}
