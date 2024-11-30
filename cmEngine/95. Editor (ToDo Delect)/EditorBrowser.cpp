#include "0. cmEngine/cmEngine.h"
#include "EditorBrowser.h"

namespace cmEngine
{
	EditorBrowser::EditorBrowser()
	{
		if (JsonSerializer::Ref().DeserializeFromSection(
			mConfig,
			Editor::sEditorConfigPath,
			"EditorBrowser"
		))
		{
			SetVisible(mConfig.visible);
		}

		SetHotKey(eKeyCode::F9);
	}

	EditorBrowser::~EditorBrowser()
	{
		mConfig.visible = IsVisible();
		JsonSerializer::Ref().SerializeToSection(mConfig, Editor::sEditorConfigPath, "EditorBrowser");
	}

	void EditorBrowser::RenderGui()
	{
	}
}
