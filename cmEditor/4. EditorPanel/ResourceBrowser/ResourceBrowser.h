#pragma once

struct ResourceBrowserJson
{
	bool	visible = false;
	float	zoom = 1.f;

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

	template<typename Ty>
	void DrawSelectableResource();
	void DrawTextureBrowser();

	bool AssetButton(const char* stringID, Texture* inTex, const ImVec2& inButtonSize,
		const ImVec4& inBgColor, const ImVec2& uv0 = { 0, 0 }, const ImVec2& uv1 = { 1, 1 })
	{
		ImGuiContext& g = *GImGui;
		ImGuiWindow* window = g.CurrentWindow;
		if (window->SkipItems) return false;

		const ImVec2 padding = g.Style.FramePadding;
		const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + inButtonSize);
		ImGui::ItemSize(bb);
		ImGuiID id = window->GetID(stringID);
		if (!ImGui::ItemAdd(bb, id)) return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, ImGuiButtonFlags_MouseButtonLeft);

		ImGuiCol buttonColorIdx = (held && hovered) ? ImGuiCol_ButtonActive
			: hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button;
		const ImU32 col = ImGui::GetColorU32(buttonColorIdx);
		ImGui::RenderFrame(bb.Min, bb.Max, col, true, g.Style.FrameRounding);

		if (inBgColor.w > 0.0f)
		{
			window->DrawList->AddRectFilled(bb.Min + padding, bb.Max - padding, ImGui::GetColorU32(inBgColor));
		}

		const float textPad = ImGui::GetTextLineHeightWithSpacing();
		ImVec2 imageAreaMin = bb.Min + padding;
		ImVec2 imageAreaMax = bb.Max - padding;
		imageAreaMax.y -= textPad;

		const auto& [textureWidth, textureHeight] = inTex->GetSize();
		const float textureAspect = textureWidth / static_cast<float>(textureHeight);

		const ImVec2 imageSize = imageAreaMax - imageAreaMin;
		const float areaAspect = imageSize.x / imageSize.y;

		if (textureAspect > areaAspect)
		{
			const float adjustedHeight = imageSize.x / textureAspect;
			const float offsetY = (imageSize.y - adjustedHeight) * 0.5f;
			imageAreaMin.y += offsetY;
			imageAreaMax.y -= offsetY;
		}
		else
		{
			const float adjustedWidth = imageSize.y * textureAspect;
			const float offsetX = (imageSize.x - adjustedWidth) * 0.5f;
			imageAreaMin.x += offsetX;
			imageAreaMax.x -= offsetX;
		}

		ImTextureID texID = reinterpret_cast<ImTextureID>(inTex->GetShaderResourceView().Get());
		window->DrawList->AddImage(texID, imageAreaMin, imageAreaMax, uv0, uv1, ImGui::GetColorU32(ImVec4{ 1, 1, 1, 1 }));

		const float maxTextWidth = inButtonSize.x - padding.x * 2;
		const float charWidth = ImGui::CalcTextSize("W").x;
		const float ellipsisWidth = ImGui::CalcTextSize("...").x;

		std::string fullText = inTex->GetName();
		size_t textLength = fullText.size();
		ImVec2 textSize;

		if (textLength * charWidth > maxTextWidth)
		{
			size_t visibleChars = static_cast<size_t>((maxTextWidth - ellipsisWidth) / charWidth);
			fullText = fullText.substr(0, visibleChars) + "...";
			textSize = ImGui::CalcTextSize(fullText.c_str());
		}
		else
		{
			fullText = fullText;
			textSize = ImVec2(textLength * charWidth, ImGui::GetTextLineHeight());
		}

		const ImVec2 textPos = {
			bb.Min.x + (inButtonSize.x - textSize.x) * 0.5f,
			bb.Max.y - padding.y - textSize.y
		};
		const ImU32 textColor = ImGui::GetColorU32(ImGuiCol_Text);
		window->DrawList->AddText(textPos, textColor, fullText.c_str());

		if (ImGui::IsItemHovered() && ImGui::BeginTooltip())
		{
			ImGui::TextUnformatted(inTex->GetName());
			ImGui::EndTooltip();
		}

		// Drag Drop
		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload(
				ImPayload::sTexturePayload,
				reinterpret_cast<const void*>(fullText.c_str()),
				fullText.size()
			);
			ImGui::TextUnformatted(inTex->GetName());

			ImGui::EndDragDropSource();
		}

		return pressed;
	}

	TO_STRING(ResourceBrowser);

private:
	ResourceBrowserJson mJson = {};
	eResourceType		mTargetType = eResourceType::Texture;
};

template <typename Ty>
void ResourceBrowser::DrawSelectableResource()
{
	static_assert(std::is_base_of_v<ResourceBase, Ty>);
	if (ImGui::Selectable(Ty::sResourceString, mTargetType == Ty::sResourceType))
	{
		mTargetType = Ty::sResourceType;
	}
}

