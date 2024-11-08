#include "pch.h"
#include "DummyScript.h"
#include "cmGameObject.h"
#include "cmMeshRenderer.h"
#include "cmTransform.h"
#include "cmMesh.h"
#include "cmCamera.h"

void DummyScript::Initialize()
{
	mMesh = GetOwner()->CreateComponent<cmMeshRenderer>(true);
	mMesh->SetMesh(Engine->GetResourceManager()->FindResourceOrNull<cmMesh>("SimpleMesh"));

	mTrans = GetOwner()->GetTransform();
}

void DummyScript::OnStart()
{
}

void DummyScript::OnFinish()
{
}

void DummyScript::Update()
{
	static float sSpeed = 1.f;

	if (KEY_HOLD(eKeyCode::Left)) { mTrans->AddPositionX(-sSpeed * DELTA_TIME); }
	if (KEY_HOLD(eKeyCode::Right)) { mTrans->AddPositionX(sSpeed * DELTA_TIME); }
	if (KEY_HOLD(eKeyCode::Up)) { mTrans->AddPositionY(sSpeed * DELTA_TIME); }
	if (KEY_HOLD(eKeyCode::Down)) { mTrans->AddPositionY(-sSpeed * DELTA_TIME); }

	static float sScale = 1.f;

	if (KEY_HOLD(eKeyCode::A)) { mTrans->AddScaleX(-sScale * DELTA_TIME); }
	if (KEY_HOLD(eKeyCode::D)) { mTrans->AddScaleX(sScale * DELTA_TIME); }
	if (KEY_HOLD(eKeyCode::W)) { mTrans->AddScaleY(sScale * DELTA_TIME); }
	if (KEY_HOLD(eKeyCode::S)) { mTrans->AddScaleY(-sScale * DELTA_TIME); }

	static float sRotate = cmMath::DegToRad(180.f);

	if (KEY_HOLD(eKeyCode::E)) { mTrans->AddRotationZ(-sRotate * DELTA_TIME); }
	if (KEY_HOLD(eKeyCode::Q)) { mTrans->AddRotationZ(sRotate * DELTA_TIME); }
}

void DummyScript::LateUpdate()
{
}
