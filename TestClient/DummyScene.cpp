#include "pch.h"
#include "DummyScene.h"
#include "cmGameObject.h"
#include "cmSceneManager.h"
#include "cmTransform.h"
#include "cmMeshRenderer.h"
#include "DummyScript.h"
#include "CameraScript.h"

void DummyScene::EnterScene()
{
	{
		auto* obj = Engine->GetSceneManager()->GetCurrentScene()->CreateGameObject(true);
		obj->CreateComponent<DummyScript>(true);
	}

	{
		auto* obj = Engine->GetSceneManager()->GetCurrentScene()->CreateGameObject(true);
		obj->CreateComponent<CameraScript>(true);
	}
}

void DummyScene::ExitScene()
{
}
