#include "pch.h"
#include "CameraGUI.h"
#include "cmCamera.h"

void CameraGUI::Initialize()
{
	SetVisible(true);
}

void CameraGUI::RenderGUI()
{
	using namespace ImGui;
	Begin("Camera Controller", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize);

	static Vector3 position = mCmr->GetPosition();
	static float rotate     = mCmr->GetRotation().z;
	static float nearVal	= mCmr->GetNearPlane();
	static float farVal		= mCmr->GetFarPlane();
	static int mode         = 0;

	position  = mCmr->GetPosition();
	rotate 	  = cmMath::RadToDeg(mCmr->GetRotation().z);
	nearVal	  = mCmr->GetNearPlane();
	farVal 	  = mCmr->GetFarPlane();

	SeparatorText("Transform");

	Text("Position");
	Text("X"); SameLine(); if (SliderFloat("Camera Position X", &position.x, -2.f, 2.f)) { mCmr->SetPosition(position); }
	Text("Y"); SameLine(); if (SliderFloat("Camera Position Y", &position.y, -2.f, 2.f)) { mCmr->SetPosition(position); }
	Text("Z"); SameLine(); if (SliderFloat("Camera Position Z", &position.z, -2.f, 2.f)) { mCmr->SetPosition(position); }

	Separator();
	Text("Rotation");
	if (SliderFloat("Camera Rotate", &rotate, 0.f, 360.f)) { mCmr->SetRotationZ(cmMath::DegToRad(rotate)); }

	Separator();
	Text("Clipping Planes");
	Text("Near"); SameLine(); if (SliderFloat("Near Plane", &nearVal, 0.1f, 10.f)) { mCmr->SetNearPlane(nearVal); }
	Text("Far"); SameLine(); if (SliderFloat("Far Plane", &farVal, 0.1f, 100.f)) { mCmr->SetFarPlane(farVal); }

	SeparatorText("Projection Mode");
	if (RadioButton("Orthographic", &mode, 0)) { mCmr->SetProjectionMode(eProjectionMode::Orthographic); }
	SameLine();
	if (RadioButton("Perspective", &mode, 1)) { mCmr->SetProjectionMode(eProjectionMode::Perspective); }

	if (mCmr->GetProjectionMode() == eProjectionMode::Perspective)
	{
		SeparatorText("Perspective Options");

		static float mFov = mCmr->GetFieldOfView();
		mFov = cmMath::RadToDeg(mCmr->GetFieldOfView());
		if (SliderFloat("Field Of View", &mFov, 1.f, 180.f)) { mCmr->SetFieldOfView(cmMath::DegToRad(mFov)); }
	}
	else
	{
		SeparatorText("Orthographic Options");

		static auto [width, height] = mCmr->GetCameraResolution();
		static bool fixRatio = true;

		if (Checkbox("Fix Aspect Ratio", &fixRatio))
		{
			auto [newWidth, newHeight] = mCmr->GetCameraResolution();
			width = newWidth;
			height = newHeight;
		}

		Text("Resolution");
		Text("Width"); SameLine(); if (SliderFloat("Width", &width, 0.01f, 10.f) || fixRatio) { mCmr->SetCameraResolutionRatio(height); }
		Text("Height"); SameLine(); if (SliderFloat("Height", &height, 0.01f, 10.f)) { mCmr->SetCameraResolution(width, height); }
	}

	if (Button("Reset"))
	{
		mCmr->SetPosition(Vector3{0.f,0.f,-1.f});
		mCmr->SetRotation(Vector3::Zero);
	}

	End();
}
