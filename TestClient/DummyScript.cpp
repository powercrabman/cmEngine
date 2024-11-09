#include "pch.h"
#include "DummyScript.h"
#include "cmGameObject.h"
#include "cmMeshRenderer.h"
#include "cmTransform.h"
#include "cmMesh.h"
#include "cmCamera.h"
#include "PlayerGUI.h"
#include "cmGraphicsResourceManager.h"

void DummyScript::Initialize()
{
	auto* rm = Engine->GetResourceManager();

	cmPipelineData pd = {};
	pd.Mesh = rm->FindResourceOrNull<cmMesh>("SimpleTexMesh");
	pd.PixelShader = rm->FindResourceOrNull<cmPixelShader>("SimpleTexPS");
	pd.VertexShader = rm->FindResourceOrNull<cmVertexShader>("SimpleTexVS");
	pd.Texture = rm->FindResourceOrNull<cmTexture>("SimpleTexture");
	pd.SamplerState = Engine->GetRenderer()->GetGraphicsResourceManager()->FindSamplerState(
		eSamplerStateFilter::Linear, eSamplerStateAddress::Clamp, eSamplerStateAddress::Clamp
	);

	mMR = GetOwner()->CreateComponent<cmMeshRenderer>(true);
	mMR->SetPipelineData(pd);

	mTrans = GetOwner()->GetTransform();

	auto* gui = cmHelper::RegisterGUI<PlayerGUI>();
	gui->SetEntity(GetOwner());
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
