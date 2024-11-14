#include "pch.h"
#include "DummyScript.h"
#include "cmGameObject.h"
#include "cmMeshRenderer.h"
#include "cmTransform.h"
#include "cmMesh.h"
#include "cmCamera.h"
#include "cmGraphicsResourceManager.h"
#include "cmFlipbookRenderer.h"
#include "cmFlipbook.h"
#include "cmEditorComponent.h"

void DummyScript::Setup()
{
	auto* rm = Engine->GetResourceManager();

	auto* fb = GetOwner()->CreateComponent<cmFlipbookRenderer>(true);
	fb->SetShaders(
		rm->FindResourceOrNull<cmVertexShader>("SimpleTexSpriteVS"),
		rm->FindResourceOrNull<cmPixelShader>("SimpleTexSpritePS")
	);
	fb->SetFlipbook(rm->FindResourceOrNull<cmFlipbook>("SimpleFlipbook"));

	mTrans = GetOwner()->GetTransform();

	cmEditorComponent* gc = GetOwner()->CreateComponent<cmEditorComponent>(true, [this]() {GUILayout(); });
	gc->GetGUI()->SetVisible(true);
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

void DummyScript::FinalUpdate()
{
}

void DummyScript::GUILayout()
{
	using namespace ImGui;
	Begin("Player Controller", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize);

	static Vector3 playerPosition = Vector3::Zero;
	playerPosition = mTrans->GetPosition();

	SeparatorText("Transform");

	Text("Position");
	Text("X"); SameLine(); if (SliderFloat("PositionX", &playerPosition.x, -3.f, 3.f)) { mTrans->SetPosition(playerPosition); }
	Text("Y"); SameLine(); if (SliderFloat("PositionY", &playerPosition.y, -3.f, 3.f)) { mTrans->SetPosition(playerPosition); }
	Text("Z"); SameLine(); if (SliderFloat("PositionZ", &playerPosition.z, -3.f, 3.f)) { mTrans->SetPosition(playerPosition); }
	Separator();

	static Vector3 playerR = Vector3::Zero;
	playerR = mTrans->GetRotation();

	Text("Rotation");
	Text("Pitch");	SameLine(); if (SliderFloat("Pitch", &playerR.x, 0.f, 360.f)) { playerR.x = cmMath::DegToRad(playerR.x); mTrans->SetRotation(playerR); }
	Text("Yaw");	SameLine(); if (SliderFloat("Yaw", &playerR.y, 0.f, 360.f)) { playerR.y = cmMath::DegToRad(playerR.y);   mTrans->SetRotation(playerR); }
	Text("Roll");	SameLine(); if (SliderFloat("Roll", &playerR.z, 0.f, 360.f)) { playerR.z = cmMath::DegToRad(playerR.z);  mTrans->SetRotation(playerR); }

	Separator();
	static Vector3 playerS = Vector3::One;
	playerS = mTrans->GetScale();
	Text("Scale");

	Text("X"); SameLine(); if (SliderFloat("ScaleX", &playerS.x, 0.01f, 5.f)) { mTrans->SetScale(playerS); }
	Text("Y"); SameLine(); if (SliderFloat("ScaleY", &playerS.y, 0.01f, 5.f)) { mTrans->SetScale(playerS); }
	Text("Z"); SameLine(); if (SliderFloat("ScaleZ", &playerS.z, 0.01f, 5.f)) { mTrans->SetScale(playerS); }

	if (Button("Reset"))
	{
		mTrans->SetPosition(Vector3::Zero);
		mTrans->SetRotation(Vector3::Zero);
		mTrans->SetScale(Vector3::One);
	}

	End();
}
