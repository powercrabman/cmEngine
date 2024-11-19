#include "EnginePch.h"
#include "EditorSceneViewer.h"

namespace cmEngine
{
	EditorSceneViewer::EditorSceneViewer()
	{
		JsonSerializer::Deserialize(mConfig);
		SetVisible(mConfig.visible);
		SetHotKey(eKeyCode::F7);
	}

	EditorSceneViewer::~EditorSceneViewer()
	{
		mConfig.visible = IsVisible();
		JsonSerializer::Serialize(mConfig);
	}

	void EditorSceneViewer::RenderGui()
	{
		// TODO: 카메라 설정, 엔티티 추적
		ImGui::Begin("Hello World!", GetVisiblePtr());
		ImGui::Text("Hello This is editor scene viewer");
		ImGui::End();
		
	}

	void EditorSceneViewer::DrawEntityEditor()
	{
		// TODO: 엔티티
	}

}
