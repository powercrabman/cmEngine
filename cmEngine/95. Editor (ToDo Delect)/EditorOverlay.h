#pragma once

namespace cmEngine
{
	struct EditorOverlayConfig : public JsonStructBase
	{
		float	transparency  = 0.5f;
		bool	noMoveBit     = true;
		bool	frameViewBit  = true;
		bool	memoryViewBit = true;
		bool	visible       = true;

		JSON_STRUCT_BODY(
			EditorOverlayConfig,
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

