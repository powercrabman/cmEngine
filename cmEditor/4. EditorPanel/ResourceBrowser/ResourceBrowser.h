#pragma once

struct ResourceBrowserJson
{
	bool visible = false;
	float zoom = 1.f;

	JSON_STRUCT_BODY(
		ResourceBrowserJson,
		visible,
		zoom
	);
};

class ResourceBrowser : public Gui
{
public:
	ResourceBrowser();
	~ResourceBrowser() override;
	void RenderGui() override;

	TO_STRING(ResourceBrowser);

private:
	void DrawResourceBrowser();
	void DrawResourceTypeSelector();
	void DrawResourceItemPopup();

	bool AssetButton(
		const char* stringID,
		ResourceBase* resource,
		const ImVec2& buttonSize,
		const ImVec4& bgColor = ImVec4(1, 1, 1, 0)
	) const;

	ResourceBrowserJson mJson = {};
	eResourceType mTargetType = eResourceType::Texture;
};
