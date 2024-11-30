#include "0. cmEditor/cmEditor.h"
#include "ResourceBrowser.h"

ResourceBrowser::ResourceBrowser()
{
	if (JSON_SERIALIZER.DeserializerFromFileWithTag(mJson, Config::gEditorPanelConfigFileName, sClassName))
	{
		SetVisible(mJson.visible);
	}
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

	static float ResourceTypeWindowWidth = 200.f;
	ImGui::BeginGroup();
	ImGui::TextWrapped("Resource Type");

	static const float buttonHeight = 20.f;
	if (ImGui::BeginChild("Resource Type", { ResourceTypeWindowWidth, ImGui::GetContentRegionAvail().y - buttonHeight }, ImGuiChildFlags_Border))
	{
		if (ImGui::BeginChild("Resource Type"))
		{
			DrawSelectableResource<Texture>();
			DrawSelectableResource<Sprite>();
			DrawSelectableResource<Flipbook>();
			DrawSelectableResource<ShaderSet>();
			ImGui::EndChild();
		}
		ImGui::EndChild();

		float pad = GImGui->Style.FramePadding.x * 2;
		float buttonWidth = (ResourceTypeWindowWidth - pad) * 0.5f;
		ImGui::Button("Import Res", ImVec2{ buttonWidth, 0.f });
		ImGui::SameLine();
		ImGui::Button("Export Res", ImVec2{ buttonWidth, 0.f });

		ImGui::EndGroup();
	}
	ImGui::SameLine();
	ImGui::BeginGroup();
	ImGui::TextWrapped("Resource Browser");
	ImGui::SetNextItemWidth(300);
	ImGui::SameLine(0, ImGui::GetContentRegionAvail().x - 500);
	ImGui::SliderFloat("Browser Zoom", &mJson.zoom, 0.5f, 2.f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

	if (ImGui::BeginChild("Resource Browser", { ImGui::GetContentRegionAvail().x , 0.f }, ImGuiChildFlags_Border))
	{
		DrawTextureBrowser();
		ImGui::EndChild();
	}
	ImGui::EndGroup();

	ImGui::End();
}

void ResourceBrowser::DrawTextureBrowser()
{
	uint32 availX        = static_cast<uint32>(ImGui::GetContentRegionAvail().x);
	float thumbNailWidth = 160 * mJson.zoom;
	int32 thumbNailCount = max(1, availX / thumbNailWidth);
	int32 gab            = thumbNailCount == 1 ? 0 : (availX % static_cast<uint32>(thumbNailWidth)) / (thumbNailCount - 1);

	auto begin              = RESOURCE_MANAGER.GetBegin<Texture>();
	const size_t totalItems = RESOURCE_MANAGER.GetResourceListSize<Texture>();

	int totalRows    = (totalItems + thumbNailCount - 1) / thumbNailCount;

	ImGuiListClipper clipper;
	clipper.Begin(totalRows, thumbNailWidth);

	while (clipper.Step())
	{
		for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; ++row)
		{
			for (int col = 0; col < thumbNailCount; ++col)
			{
				int itemIndex = row * thumbNailCount + col;
				if (itemIndex >= totalItems)
					break;

				auto iter = std::next(begin, itemIndex);
				Texture* tex = static_cast<Texture*>(iter->second.get());
				AssetButton(tex->GetName(), tex, { thumbNailWidth, thumbNailWidth }, ImVec4{ 1, 1, 1, 0 });
				// Drag Drop
				if (ImGui::BeginDragDropSource())
				{
					ImGui::SetDragDropPayload(
						ImPayload::sTexturePayload,
						reinterpret_cast<const void*>(tex->GetName()),
						::strlen(tex->GetName())
					);
					static float previewLen = 32.f;
					ImGui::TextUnformatted(tex->GetName());

					ImGui::EndDragDropSource();
				}

				if ((col + 1) < thumbNailCount)
				{
					ImGui::SameLine(0.f, gab);
				}
			}
		}
	}
}