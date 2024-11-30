#include "0. cmEditor/cmEditor.h"
#include "ResourceBrowser.h"

ResourceBrowser::ResourceBrowser()
{
	if (JSON_SERIALIZER.DeserializerFromFileWithTag(mJson, Config::gEditorPanelConfigFileName, sClassName))
	{
		SetVisible(mJson.visible);
	}

	// 기본 아이콘 텍스처 로드
	mDefaultIconTexture = RESOURCE_MANAGER.CreateEmptyResource<Texture>("DefaultIcon");
	mDefaultIconTexture->LoadTextureImage(L"EditorInnerResources\\DocIcon.png");
}

ResourceBrowser::~ResourceBrowser()
{
	mJson.visible = IsVisible();
	JSON_SERIALIZER.SerializeToFileWithTag(mJson, Config::gEditorPanelConfigFileName, sClassName);
}

void ResourceBrowser::RenderGui()
{
	ImGui::SetNextWindowSize({ 500, 300 }, ImGuiCond_FirstUseEver);
	ImGui::Begin("Resource Browser", GetVisiblePtr(), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	// 리소스 타입 선택기
	DrawResourceTypeSelector();

	ImGui::SameLine();

	// 리소스 브라우저
	DrawResourceBrowser();

	ImGui::End();
}

void ResourceBrowser::DrawResourceTypeSelector()
{
	static float resourceTypeWidth = 200.f;
	ImGui::BeginGroup();
	ImGui::TextWrapped("Resource Type");

	if (ImGui::BeginChild("Resource Type", { resourceTypeWidth, 0 }, ImGuiChildFlags_Border))
	{
		for (int type = static_cast<int32>(eResourceType::Texture); type < static_cast<uint32>(eResourceType::Count); ++type)
		{
			const char* typeName = cmEngine::ToString(static_cast<eResourceType>(type));
			if (ImGui::Selectable(typeName, static_cast<uint32>(mTargetType) == type))
			{
				mTargetType = static_cast<eResourceType>(type);
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndGroup();
}

void ResourceBrowser::DrawResourceBrowser()
{
	ImGui::BeginGroup();
	ImGui::TextWrapped("Resource Browser");

	static const float	zoomSliderWidth = 300;
	float				zoomTextWidth   = ImGui::CalcTextSize("Zoom").x;

	ImGui::SetNextItemWidth(zoomSliderWidth);
	ImGui::SameLine(ImGui::GetContentRegionAvail().x - zoomTextWidth - zoomSliderWidth - GImGui->Style.FramePadding.x);
	ImGui::SliderFloat("Zoom", &mJson.zoom, 0.5f, 2.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

	if (ImGui::BeginChild("Resource Browser", { ImGui::GetContentRegionAvail().x, 0 }, ImGuiChildFlags_Border))
	{
		const auto& resources = RESOURCE_MANAGER.GetBegin(mTargetType);
		size_t      resourceSize = RESOURCE_MANAGER.GetResourceListSize(mTargetType);

		uint32_t availX        = static_cast<uint32_t>(ImGui::GetContentRegionAvail().x);
		float thumbnailWidth   = 160 * mJson.zoom;
		int32_t thumbnailCount = max(1, static_cast<int32_t>(availX / thumbnailWidth));
		int32_t gap            = thumbnailCount == 1 ? 0 : (availX % static_cast<uint32_t>(thumbnailWidth)) / (thumbnailCount - 1);

		int totalRows = (resourceSize + thumbnailCount - 1) / thumbnailCount;

		ImGuiListClipper clipper;
		clipper.Begin(totalRows, thumbnailWidth);

		while (clipper.Step())
		{
			for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; ++row)
			{
				for (int col = 0; col < thumbnailCount; ++col)
				{
					int itemIndex = row * thumbnailCount + col;
					if (itemIndex >= resourceSize)
						break;

					ResourceBase* resource = std::next(resources, itemIndex)->second.get();
					AssetButton(resource->GetName(), resource, { thumbnailWidth, thumbnailWidth });
					DrawResourceItemPopup();

					// 드래그 & 드롭 지원
					if (ImGui::BeginDragDropSource())
					{
						ImGui::SetDragDropPayload(
							ImPayload::GetResourcePayload(mTargetType),
							resource->GetName(),
							strlen(resource->GetName()) + 1
						);
						ImGui::TextUnformatted(resource->GetName());
						ImGui::EndDragDropSource();
					}

					if ((col + 1) < thumbnailCount)
					{
						ImGui::SameLine(0.f, gap);
					}
				}
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndGroup();
}

bool ResourceBrowser::AssetButton(
	const char* stringID,
	ResourceBase* resource,
	const ImVec2& buttonSize,
	const ImVec4& bgColor) const
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;
	if (window->SkipItems)
		return false;

	ImVec2 padding = g.Style.FramePadding;
	ImRect bb(window->DC.CursorPos, window->DC.CursorPos + buttonSize);
	ImGui::ItemSize(bb);
	ImGuiID id = window->GetID(stringID);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, ImGuiButtonFlags_MouseButtonLeft);

	ImGuiCol buttonColorIdx = (held && hovered) ? ImGuiCol_ButtonActive
		: hovered ? ImGuiCol_ButtonHovered
		: ImGuiCol_Button;
	ImU32 col = ImGui::GetColorU32(buttonColorIdx);
	ImGui::RenderFrame(bb.Min, bb.Max, col, true, g.Style.FrameRounding);

	if (bgColor.w > 0.0f)
	{
		window->DrawList->AddRectFilled(bb.Min + padding, bb.Max - padding, ImGui::GetColorU32(bgColor));
	}

	float textPad       = ImGui::GetTextLineHeightWithSpacing();
	ImVec2 imageAreaMin = bb.Min + padding;
	ImVec2 imageAreaMax = bb.Max - padding;
	imageAreaMax.y     -= textPad;

	Texture* displayTexture = nullptr;

	switch (resource->GetResourceType())
	{
	case eResourceType::Texture:	displayTexture = static_cast<Texture*>(resource); break;
	case eResourceType::Sprite:		displayTexture = static_cast<Sprite*>(resource)->GetSpriteData().texture; break;
	case eResourceType::Flipbook:	displayTexture = static_cast<Flipbook*>(resource)->GetFlipbookData().texture; break;
	case eResourceType::ShaderSet:	displayTexture = mDefaultIconTexture; break;
	default:						displayTexture = mDefaultIconTexture; assert(false); break;
	}

	const auto& [textureWidth, textureHeight] = displayTexture->GetSize();
	float textureAspect                       = textureWidth / static_cast<float>(textureHeight);
	ImVec2 imageSize                          = imageAreaMax - imageAreaMin;
	float areaAspect                          = imageSize.x / imageSize.y;

	if (textureAspect > areaAspect)
	{
		const float adjustedHeight = imageSize.x / textureAspect;
		const float offsetY        = (imageSize.y - adjustedHeight) * 0.5f;
		imageAreaMin.y            += offsetY;
		imageAreaMax.y            -= offsetY;
	}
	else
	{
		const float adjustedWidth = imageSize.y * textureAspect;
		const float offsetX       = (imageSize.x - adjustedWidth) * 0.5f;
		imageAreaMin.x           += offsetX;
		imageAreaMax.x           -= offsetX;
	}

	ImTextureID texID = reinterpret_cast<ImTextureID>(displayTexture->GetShaderResourceView().Get());
	window->DrawList->AddImage(texID, imageAreaMin, imageAreaMax);

	const float maxTextWidth = buttonSize.x - padding.x * 2;
	std::string fullText     = resource->GetName();
	ImVec2 textSize          = ImGui::CalcTextSize(fullText.c_str());

	if (textSize.x > maxTextWidth)
	{
		size_t visibleString = maxTextWidth / ImGui::CalcTextSize("C").x;
		fullText             = fullText.substr(0, visibleString - 2) + "..";
		textSize             = ImGui::CalcTextSize(fullText.c_str());
	}

	const ImVec2 textPos = {
		bb.Min.x + (buttonSize.x - textSize.x) * 0.5f,
		bb.Max.y - padding.y - textSize.y
	};
	window->DrawList->AddText(textPos, ImGui::GetColorU32(ImGuiCol_Text), fullText.c_str());

	// 툴팁
	if (ImGui::IsItemHovered() && ImGui::BeginTooltip())
	{
		ImGui::TextUnformatted(resource->GetName());
		ImGui::EndTooltip();
	}

	return pressed;
}

