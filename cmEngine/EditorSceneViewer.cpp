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
		// TODO: ī�޶� ����, ��ƼƼ ����
		ImGui::Begin("Hello World!", GetVisiblePtr());
		ImGui::Text("Hello This is editor scene viewer");
		ImGui::End();
		
	}

	void EditorSceneViewer::DrawEntityEditor()
	{
		// TODO: ��ƼƼ
	}

}
