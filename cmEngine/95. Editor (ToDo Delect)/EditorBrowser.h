#pragma once
namespace cmEngine
{
	struct EditorBrowserJson : JsonStructBase
	{
		bool visible;

		JSON_STRUCT_BODY(
			EditorBrowserJson,
			visible
		)
	};

	class EditorBrowser : public Gui
	{
	public:
		EditorBrowser();
		~EditorBrowser() override;

		void RenderGui() override;

	private:
		EditorBrowserJson mConfig = {};
	};
}
