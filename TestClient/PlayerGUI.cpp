#include "pch.h"
#include "PlayerGUI.h"
#include "cmGameObject.h"
#include "cmMeshRenderer.h"
#include "cmTransform.h"
#include "cmMesh.h"

void PlayerGUI::Initialize()
{
}

void PlayerGUI::RenderGUI()
{
	using namespace ImGui;
	Begin("Player Controller", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize);

	static Vector3 playerPosition = Vector3::Zero;
	playerPosition = t->GetPosition();

	SeparatorText("Transform");

	Text("Position");
	Text("X"); SameLine(); if (SliderFloat("PositionX", &playerPosition.x, -3.f, 3.f)) { t->SetPosition(playerPosition); }
	Text("Y"); SameLine(); if (SliderFloat("PositionY", &playerPosition.y, -3.f, 3.f)) { t->SetPosition(playerPosition); }
	Text("Z"); SameLine(); if (SliderFloat("PositionZ", &playerPosition.z, -3.f, 3.f)) { t->SetPosition(playerPosition); }
	Separator();

	static Vector3 playerR = Vector3::Zero;
	playerR = t->GetRotation();

	Text("Rotation");
	Text("Pitch");	SameLine(); if (SliderFloat("Pitch", &playerR.x, 0.f, 360.f)) { playerR.x = cmMath::DegToRad(playerR.x); t->SetRotation(playerR); }
	Text("Yaw");	SameLine(); if (SliderFloat("Yaw", &playerR.y, 0.f, 360.f)) { playerR.y = cmMath::DegToRad(playerR.y);   t->SetRotation(playerR); }
	Text("Roll");	SameLine(); if (SliderFloat("Roll", &playerR.z, 0.f, 360.f)) { playerR.z = cmMath::DegToRad(playerR.z);  t->SetRotation(playerR); }
	
	Separator();
	static Vector3 playerS = Vector3::One;
	playerS = t->GetScale();
	Text("Scale");

	Text("X"); SameLine(); if (SliderFloat("ScaleX", &playerS.x, 0.01f, 5.f)) { t->SetScale(playerS); }
	Text("Y"); SameLine(); if (SliderFloat("ScaleY", &playerS.y, 0.01f, 5.f)) { t->SetScale(playerS); }
	Text("Z"); SameLine(); if (SliderFloat("ScaleZ", &playerS.z, 0.01f, 5.f)) { t->SetScale(playerS); }

	if (Button("Reset"))
	{
		t->SetPosition(Vector3::Zero);
		t->SetRotation(Vector3::Zero);
		t->SetScale(Vector3::One);
	}

	End();
}

void PlayerGUI::SetEntity(cmGameObject* inObj)
{
	mObj = inObj;
	t = mObj->GetTransform();
	r = mObj->FindComponentOrNull<cmMeshRenderer>();
}
