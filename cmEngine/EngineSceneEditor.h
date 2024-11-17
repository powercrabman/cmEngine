#pragma once
#include "ConfigBase.h"

namespace cmEngine
{
	struct EngineSceneEditorConfig : public ConfigBase
	{
		bool Visible        = false;
		bool EntityEditView = false;

		CONFIG_BODY(
			EngineSceneEditorConfig,
			L"SystemConfig.json",
			Visible,
			EntityEditView
		)
	};

	class EngineSceneEditor : public GuiFrame
	{
	public:
		EngineSceneEditor() { ConfigEngine::Save(mConfig); }
		virtual ~EngineSceneEditor();

		void Initialize() override;
		void GuiLayout() override;

		void DrawEntityEditor();

	private:
		EngineSceneEditorConfig mConfig = {};
		GameEntity* mTargetEntity = nullptr;
	};
}

