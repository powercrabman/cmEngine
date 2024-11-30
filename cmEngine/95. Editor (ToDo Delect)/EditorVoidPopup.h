#pragma once

namespace cmEngine
{
	class EditorVoidPopup : public Gui
	{
	public:
				EditorVoidPopup();
		virtual ~EditorVoidPopup() override = default;

		void	RenderGui()			override;
		void	DrawClearColor();

	private:
		bool mClearColorBit = false;
	};
}



