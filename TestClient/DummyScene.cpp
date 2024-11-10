#include "pch.h"
#include "DummyScene.h"
#include "cmGameObject.h"
#include "cmSceneManager.h"
#include "cmTransform.h"
#include "cmMeshRenderer.h"
#include "DummyScript.h"
#include "CameraScript.h"
#include "cmSpriteRenderer.h"
#include "cmSprite.h"
#include "cmVertexShader.h"

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

	//{
	//	auto* r = Engine->GetResourceManager();
	//	auto* obj = Engine->GetSceneManager()->GetCurrentScene()->CreateGameObject(true);
	//	auto* sp = obj->CreateComponent<cmSpriteRenderer>(true);
	//	sp->SetShaders(r->FindResourceOrNull<cmVertexShader>("SimpleTexSpriteVS"), r->FindResourceOrNull<cmPixelShader>("SimpleTexSpritePS"));
	//	sp->SetSprite(r->FindResourceOrNull<cmSprite>("SimpleSprite"));
	//	obj->GetTransform()->SetPosition({0.f, 0.f, 3.f});
	//}
}

void DummyScene::ExitScene()
{
}
