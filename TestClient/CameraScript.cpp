#include "pch.h"
#include "CameraScript.h"
#include "cmTransform.h"
#include "cmGameObject.h"
#include "cmCamera.h"
#include "CameraGUI.h"

void CameraScript::Initialize()
{
	t = GetOwner()->GetTransform();
	cmr = GetOwner()->CreateComponent<cmCamera>(true, t);
	cmr->SetupOrthographicRatio(1.f, 0.1f, 100.f);

	auto* gui = cmHelper::RegisterGUI<CameraGUI>();
	gui->SetCameraObject(cmr);
}

void CameraScript::OnStart()
{
	t->SetPosition(Vector3{ 0.f,0.f, -1.f });
}

void CameraScript::OnFinish()
{
}

void CameraScript::Update()
{
}

void CameraScript::LateUpdate()
{
}