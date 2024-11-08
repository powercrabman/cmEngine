#include "pch.h"
#include "CameraGUI.h"
#include "cmCamera.h"

void CameraGUI::Initialize()
{
	SetVisible(true);
}

void CameraGUI::RenderGUI()
{
	ImGui::Begin("Camera Controller", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize);

	static Vector3 position = mCmr->GetPosition();
	static bool isPositionChanged = false;
	if (ImGui::SliderFloat("Camera Position X", &position.x, -2.f, 2.f)) { isPositionChanged = true; }
	if (ImGui::SliderFloat("Camera Position Y", &position.y, -2.f, 2.f)) { isPositionChanged = true; }
	if (ImGui::SliderFloat("Camera Position Z", &position.z, -2.f, 2.f)) { isPositionChanged = true; }

	if (isPositionChanged)
	{
		mCmr->SetPosition(position);
		isPositionChanged = false;
	}

	static float rotate = mCmr->GetRotation().y;
	static bool isRotateChanged = false;
	if (ImGui::SliderFloat("Camera Rotate", &rotate, 0.f, 360.f)) { isRotateChanged = true; }

	if (isRotateChanged)
	{
		mCmr->SetRotationZ(cmMath::DegToRad(rotate));
		isRotateChanged = false;
	}

	static float nearVal = mCmr->GetNearPlane();
	static bool isNearChg = false;
	if (ImGui::SliderFloat("Near Plann", &nearVal, 0.1f, 10.f)) { isNearChg = true; }

	if (isNearChg)
	{
		mCmr->SetNearPlane(nearVal);
		isNearChg = false;
	}

	static float farVal = mCmr->GetFarPlane();
	static bool isFarChg = false;
	if (ImGui::SliderFloat("Far Plann", &farVal, 0.1f, 100.f)) { isFarChg = true; }

	if (isFarChg)
	{
		mCmr->SetFarPlane(farVal);
		isFarChg = false;
	}


	ImGui::Separator();
	ImGui::Text("Camera Projection Mode");

	static int mode = 0;
	static bool isModeChanged = false;
	if (ImGui::RadioButton("Orthographic", &mode, 0)) { isModeChanged = true; };
	if (ImGui::RadioButton("Perspcetive", &mode, 1)) { isModeChanged = true; };

	if (isModeChanged)
	{
		if (mode == 0) { mCmr->SetProjectionMode(eProjectionMode::Orthographic); }
		else if (mode == 1) { mCmr->SetProjectionMode(eProjectionMode::Perspective); }

		isModeChanged = false;
	}

	ImGui::Separator();
	if (mCmr->GetProjectionMode() == eProjectionMode::Perspective)
	{
		ImGui::Text("Perspective Options");

		static float mFov = mCmr->GetFieldOfView();
		static bool isFovChanged = false;
		if (ImGui::SliderFloat("Field Of View", &mFov, 1.f, 180.f)) { isRotateChanged = true; }

		if (isFovChanged)
		{
			mCmr->SetFieldOfView(mFov);
			isFovChanged = false;
		}
	}
	else
	{
		ImGui::Text("Orthographic Options");

		static auto [width, height] = mCmr->GetCameraScreenSize();
		static bool isSizeChanged = false;
		static bool fixRatio = true;

		if (ImGui::Checkbox("Fix Aspect Ratio", &fixRatio))
		{
			auto [newWidth, newHeight] = mCmr->GetCameraScreenSize();
			width = newWidth;
			height = newHeight;
			isSizeChanged = true; 
		};

		if (fixRatio)
		{
			if (ImGui::SliderFloat("Height", &height, 0.01f, 10.f)) { isSizeChanged = true; }
		}
		else
		{
			if (ImGui::SliderFloat("Width", &width, 0.01f, 10.f)) { isSizeChanged = true; }
			if (ImGui::SliderFloat("Height", &height, 0.01f, 10.f)) { isSizeChanged = true; }
		}

		if (isSizeChanged)
		{
			if (fixRatio) { mCmr->SetCameraScreenSizeMatchAspectRatio(height); }
			else { mCmr->SetCameraScreenSize(width, height); }
			
			isSizeChanged = false;
		}
	}

	ImGui::End();
}
