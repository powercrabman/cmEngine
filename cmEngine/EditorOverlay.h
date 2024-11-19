#pragma once

namespace cmEngine
{
	struct EditorOverlayConfig : public JsonMetaData
	{
		float	transparency  = 0.5f;
		bool	noMoveBit     = true;
		bool	frameViewBit  = true;
		bool	memoryViewBit = true;
		bool	visible       = true;

		JSON_STRUCT_BODY(
			EditorOverlayConfig,
			L"EditorConfig.json",
			transparency,
			noMoveBit,
			frameViewBit,
			memoryViewBit,
			visible
		);
	};

	//===================================================

	class EditorOverlay : public Gui
	{
	public:
		EditorOverlay();
		~EditorOverlay() override;

		void RenderGui() override;

	private:
		EditorOverlayConfig mConfig = {};
	};
}

