#pragma once

namespace cmEngine
{
	struct EditorResourceViewerJson : JsonStructBase
	{
		bool visible;
		bool showDetailBit;

		JSON_STRUCT_BODY(
			EditorResourceViewerJson,
			visible,
			showDetailBit
		);
	};

	class EditorResourceViewer : public Gui
	{
		struct DummyFlipbookRenderer;
	public:
		EditorResourceViewer();
		~EditorResourceViewer() override;

		void RenderGui() override;

		template<typename Ty>
		inline void DrawResourceList();

		void DrawImageOnPreview(Texture* inTexture, float aspectRatio, float width = 1.0f, float height = 1.0f, float offsetU = 0.0f, float offsetV = 0.0f);
		void DrawTexturePreview(Texture* inTexture)
		{
			DrawImageOnPreview(inTexture, inTexture->GetAspectRatio());
		}
		void DrawSpritePreview(const SpriteData& inSpData);
		void DrawFlipbookPreview(const FlipbookData& inFbData, DummyFlipbookRenderer& inDummyFPR);
		void DrawDefaultPreview()
		{
			GuiHelper::TextColoredCenterAlign("Previews are not provided.", ToImVec4(Colors::Gray));
		}

		void ShowSpriteDetail();
		void ShowTextureDetail();
		void ShowFlipbookDetail();
		void ShowDefaultDetail()
		{
			GuiHelper::TextColoredWrapCenterAlign("Unable to provide information.", ToImVec4(Colors::Gray));
		}
		void ShowShaderSetDetail();

	private:
		struct DummyFlipbookRenderer
		{
			void Clear() { curFrame = 0; timeAcc = 0.f; finish = false; play = true; }

			uint32		curFrame = 0;
			float		timeAcc = 0.f;
			bool		finish = false;
			bool		play = true;
		};

		EditorResourceViewerJson	mConfig = {};
		ResourceBase* mTargetRes = nullptr;
	};

	template <typename Ty>
	void EditorResourceViewer::DrawResourceList()
	{
		static_assert(std::is_base_of_v<ResourceBase, Ty>);

		if (ImGui::BeginTabItem(Ty::sResourceString))
		{
			if (ImGui::BeginChild("Resource List", ImVec2{ 0, - ImGui::GetFrameHeightWithSpacing() }, ImGuiChildFlags_Border))
			{
				for (auto iter = ResourceManager::Ref().GetBegin<Ty>(); iter != ResourceManager::Ref().GetEnd<Ty>(); ++iter)
				{
					if (ImGui::Selectable(iter->first.c_str(), iter->second.get() == mTargetRes))
					{
						mTargetRes = iter->second.get();
					}
					ImGui::Separator();
				}
				ImGui::EndChild();
			}
			ImGui::EndTabItem();

			if (ImGui::Button("Load")) {}
			ImGui::SameLine();
			if (ImGui::Button("Delect")) {}
		}
	}
}
