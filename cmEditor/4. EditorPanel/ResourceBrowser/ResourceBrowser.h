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
	void DrawResourceItemPopup()
	{
		switch (mTargetType)
		{
		case cmEngine::eResourceType::Texture:
		{
			if (ImGui::BeginPopupContextItem())
			{
				ImGui::Selectable("Import image");
				ImGui::Selectable("Create sprite");
				ImGui::Selectable("Create flipbook");
				ImGui::Separator();
				ImGui::Selectable("Refresh");
				ImGui::Selectable("Delete");
				ImGui::EndPopup();
			}
			break;
		}
		case cmEngine::eResourceType::Sprite:
		{
			if (ImGui::BeginPopupContextItem())
			{
				ImGui::EndPopup();
			}
			break;
		}
		case cmEngine::eResourceType::Flipbook:
		{
			if (ImGui::BeginPopupContextItem())
			{
				ImGui::EndPopup();
			}
			break;
		}
		case cmEngine::eResourceType::ShaderSet:
		{
			if (ImGui::BeginPopupContextItem())
			{
				ImGui::EndPopup();
			}
			break;
		}
		default: assert(false); break;
		}
	}

	bool AssetButton(
		const char* stringID,
		ResourceBase* resource,
		const ImVec2& buttonSize,
		const ImVec4& bgColor = ImVec4(1, 1, 1, 0)
	) const;

	ResourceBrowserJson mJson = {};
	eResourceType mTargetType = eResourceType::Texture;
	Texture* mDefaultIconTexture = nullptr;
};
