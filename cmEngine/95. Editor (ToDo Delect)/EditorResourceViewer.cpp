#include "0. cmEngine/cmEngine.h"
#include "EditorResourceViewer.h"

namespace cmEngine
{
	EditorResourceViewer::EditorResourceViewer()
	{
		if (JsonSerializer::Ref().DeserializeFromSection(mConfig, Editor::sEditorConfigPath, "EditorResourceViewer"))
		{
			SetVisible(mConfig.visible);
		}
		SetHotKey(eKeyCode::F8);
	}

	EditorResourceViewer::~EditorResourceViewer()
	{
		mConfig.visible = IsVisible();
		JsonSerializer::Ref().SerializeToSection(mConfig, Editor::sEditorConfigPath, "EditorResourceViewer");
	}

	void EditorResourceViewer::RenderGui()
	{
		ImGui::Begin("Resource Viewer", GetVisiblePtr());

		// Preview
		ImGui::BulletText("Preview");
		if (ImGui::BeginChild("Preview", { 0,200 }, ImGuiChildFlags_Border))
		{
			if (mTargetRes)
			{
				switch (mTargetRes->GetResourceType())
				{
				case eResourceType::Texture:
					DrawTexturePreview(static_cast<Texture*>(mTargetRes));
					break;
				case eResourceType::Sprite:
					DrawSpritePreview(static_cast<Sprite*>(mTargetRes)->GetSpriteData());
					break;
				case eResourceType::Flipbook:
				{
					static DummyFlipbookRenderer sDummyFlipbook = {};
					DrawFlipbookPreview(static_cast<Flipbook*>(mTargetRes)->GetFlipbookData(), sDummyFlipbook);
				}
				break;
				default:
					DrawDefaultPreview();
				}
			}
			else
			{
				DrawDefaultPreview();
			}

			ImGui::EndChild();

			if (ImGui::Button(mConfig.showDetailBit ? "Close Detail" : "Show Detail"))
			{
				mConfig.showDetailBit = !mConfig.showDetailBit;
			}
		}

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Close")) { mConfig.showDetailBit = false; }
			ImGui::EndPopup();
		}

		// ºä¾î
		if (ImGui::BeginTabBar("Resource Viewer"))
		{
			DrawResourceList<Texture>();
			DrawResourceList<ShaderSet>();
			DrawResourceList<Sprite>();
			DrawResourceList<Flipbook>();

			ImGui::EndTabBar();
		}
		ImVec2 viewerPos = ImGui::GetWindowPos();
		ImVec2 viewerSize = ImGui::GetWindowSize();
		ImGui::End();

		// Show Detail
		if (mConfig.showDetailBit)
		{
			ImVec2 detailPos = { viewerPos.x + viewerSize.x + 5, viewerPos.y };
			ImGui::SetNextWindowPos(detailPos, ImGuiCond_Always);
			ImGui::SetNextWindowSize({ 200, 300 }, ImGuiCond_FirstUseEver);
			ImGui::Begin("Resource viewer - Detail", &mConfig.showDetailBit);

			if (mTargetRes)
			{
				switch (mTargetRes->GetResourceType())
				{
				case eResourceType::Texture:
					ShowTextureDetail();
					break;
				case eResourceType::Sprite:
					ShowSpriteDetail();
					break;
				case eResourceType::Flipbook:
					ShowFlipbookDetail();
					break;
				case eResourceType::ShaderSet:
					ShowShaderSetDetail();
					break;
				default:
					ShowDefaultDetail();
				}
			}
			else
			{
				ShowDefaultDetail();
			}

			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::MenuItem("Close")) { mConfig.showDetailBit = false; }
				ImGui::EndPopup();
			}

			ImGui::End();
		}
	}

	void EditorResourceViewer::DrawImageOnPreview(Texture* inTexture, float aspectRatio, float width, float height,
		float offsetU, float offsetV)
	{
		ImVec2 availableSize = ImGui::GetContentRegionAvail();

		float imageWidth = availableSize.y * aspectRatio;
		float imageHeight = availableSize.y;

		if (imageWidth > availableSize.x)
		{
			imageWidth = availableSize.x;
			imageHeight = availableSize.x / aspectRatio;
		}

		float offsetPosX = (availableSize.x - imageWidth) * 0.5f;
		float offsetPosY = (availableSize.y - imageHeight) * 0.5f;

		if (offsetPosX > 0.0f) ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offsetPosX);
		if (offsetPosY > 0.0f) ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offsetPosY);

		ImTextureID texId = reinterpret_cast<ImTextureID>(inTexture->GetShaderResourceView().Get());

		ImGui::Image(
			texId,
			ImVec2(imageWidth, imageHeight),
			ImVec2(offsetU, offsetV),
			ImVec2(offsetU + width, offsetV + height)
		);
	}

	void EditorResourceViewer::DrawSpritePreview(const SpriteData& inSpData)
	{
		Texture* texture = inSpData.texture;
		auto [width, height] = texture->GetSize();

		float h = inSpData.height / static_cast<float>(height);
		float w = inSpData.width / static_cast<float>(width);
		float aspectRatio = inSpData.width / static_cast<float>(inSpData.height);

		DrawImageOnPreview(texture, aspectRatio, w, h, w * inSpData.pivotCol, h * inSpData.pivotRow);
	}

	void EditorResourceViewer::DrawFlipbookPreview(const FlipbookData& inFbData, DummyFlipbookRenderer& inDummyFPR)
	{
		Texture* texture = inFbData.texture;
		auto [width, height] = texture->GetSize();

		float h = inFbData.height / static_cast<float>(height);
		float w = inFbData.width / static_cast<float>(width);

		if (inDummyFPR.play && !inDummyFPR.finish)
		{
			inDummyFPR.timeAcc += Timer::Ref().GetDeltaTime();

			if (inDummyFPR.timeAcc >= inFbData.frameDuration)
			{
				inDummyFPR.timeAcc -= inFbData.frameDuration;

				if (inDummyFPR.curFrame < inFbData.frameCount - 1)
				{
					++inDummyFPR.curFrame;
				}
				else
				{
					if (inFbData.loop)
					{
						inDummyFPR.curFrame = 0;
					}
					else
					{
						inDummyFPR.finish = true;
					}
				}
			}
		}

		float aspectRatio = inFbData.width / static_cast<float>(inFbData.height);
		DrawImageOnPreview(texture, aspectRatio, w, h, w * (inDummyFPR.curFrame + inFbData.pivotCol), inFbData.pivotRow * h);
	}

	void EditorResourceViewer::ShowSpriteDetail()
	{
		Sprite* sp = static_cast<Sprite*>(mTargetRes);
		const SpriteData& spData = sp->GetSpriteData();
		static bool sEditBit = false;

		ImGui::Text("Resource Name : %s", sp->GetName());
		ImGui::Text("Resource Type : %s", Sprite::sResourceString);
		ImGui::Text("Resource ID : %d", sp->GetID());
		ImGui::Text("Base Texture : %s", spData.texture->GetName());
		ImGui::Text("Texture ID : %d", spData.texture->GetID());
		auto [width, height] = spData.texture->GetSize();
		ImGui::Text("Texture Width : %dpx", width);
		ImGui::Text("Texture Height : %dpx", height);

		ImGui::Separator();

		static SpriteData sEditSpriteData = {};

		if (sEditBit)
		{
			ImGui::BulletText("Edit View");
			if (ImGui::BeginChild("Edit View", ImVec2{ 0, 200 }, ImGuiChildFlags_Border))
			{
				DrawSpritePreview(sEditSpriteData);
				ImGui::EndChild();
			}
			static uint32 step = 1;
			ImGui::DragInt("Width", reinterpret_cast<int*>(&sEditSpriteData.width), 1, 1, 100000);
			ImGui::DragInt("Height", reinterpret_cast<int*>(&sEditSpriteData.height), 1, 1, 100000);
			ImGui::InputScalar("Pivot Row", ImGuiDataType_U32, (&sEditSpriteData.pivotRow), &step);
			ImGui::InputScalar("Pivot Col", ImGuiDataType_U32, (&sEditSpriteData.pivotCol), &step);

			if (ImGui::Button("Save"))
			{
				sp->Create(sEditSpriteData);
			}

			ImGui::SameLine();

			if (ImGui::Button("Exit"))
			{
				if (spData == sEditSpriteData)
				{
					sEditBit = false;
				}
				else
				{
					ImGui::OpenPopup("Save Modal");
				}
			}

			if (ImGui::BeginPopupModal("Save Modal", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::TextUnformatted("Sprite data has been modified.");

				if (ImGui::Button("Save and Close"))
				{
					sp->Create(sEditSpriteData);
					sEditBit = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				if (ImGui::Button("No save and Close"))
				{
					sEditSpriteData = spData;
					sEditBit = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				if (ImGui::Button("Cancel"))
				{
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
		else
		{
			ImGui::Text("Width : %dpx", spData.width);
			ImGui::Text("Height : %dpx", spData.height);
			ImGui::Text("Pivot Row : %d", spData.pivotRow);
			ImGui::Text("Pivot Col : %d", spData.pivotCol);

			if (ImGui::Button("Edit"))
			{
				sEditSpriteData = spData;
				sEditBit = true;
			}
		}
	}

	void EditorResourceViewer::ShowTextureDetail()
	{
		Texture* tex = static_cast<Texture*>(mTargetRes);
		ImGui::Text("Resource Name : %s", tex->GetName());
		ImGui::Text("Resource Type : %s", Texture::sResourceString);
		ImGui::Text("Resource ID : %d", tex->GetID());
		auto [width, height] = tex->GetSize();
		ImGui::Text("Texture Width : %dpx", width);
		ImGui::Text("Texture Height : %dpx", height);
	}

	void EditorResourceViewer::ShowFlipbookDetail()
	{
		Flipbook* fb = static_cast<Flipbook*>(mTargetRes);
		const FlipbookData& fbData = fb->GetFlipbookData();
		static bool sEditBit = false;

		ImGui::Text("Resource Name : %s", fb->GetName());
		ImGui::Text("Resource Type : %s", Flipbook::sResourceString);
		ImGui::Text("Resource ID : %d", fb->GetID());
		ImGui::Text("Base Texture : %s", fbData.texture->GetName());
		ImGui::Text("Texture ID : %d", fbData.texture->GetID());
		auto [width, height] = fbData.texture->GetSize();
		ImGui::Text("Texture Width : %dpx", width);
		ImGui::Text("Texture Height : %dpx", height);

		ImGui::Separator();

		static FlipbookData				sEditFlipbookData = {};
		static DummyFlipbookRenderer	sDummyFlipbook = {};

		if (sEditBit)
		{
			ImGui::BulletText("Edit View");
			if (ImGui::BeginChild("Edit View", ImVec2{ 0, 200 }, ImGuiChildFlags_Border))
			{
				DrawFlipbookPreview(sEditFlipbookData, sDummyFlipbook);
				ImGui::EndChild();
			}
			static uint32 step = 1;
			static float stepFloat = 0.01f;
			ImGui::DragInt("Width", reinterpret_cast<int*>(&sEditFlipbookData.width), 1, 1, 100000);
			ImGui::DragInt("Height", reinterpret_cast<int*>(&sEditFlipbookData.height), 1, 1, 100000);
			ImGui::InputScalar("Pivot Row", ImGuiDataType_U32, (&sEditFlipbookData.pivotRow), &step);
			ImGui::InputScalar("Pivot Col", ImGuiDataType_U32, (&sEditFlipbookData.pivotCol), &step);
			ImGui::InputScalar("Total Frame", ImGuiDataType_U32, (&sEditFlipbookData.frameCount), &step);
			ImGui::InputScalar("Flip Speed", ImGuiDataType_Float, (&sEditFlipbookData.frameDuration), &stepFloat, nullptr, "%0.2f sec");
			ImGui::Checkbox("Loop", &sEditFlipbookData.loop);

			if (ImGui::Button("Reset")) { sDummyFlipbook.Clear(); }
			ImGui::SameLine();
			static bool sPlayBit = true;
			if (ImGui::Button(sPlayBit ? "Stop" : "Play")) { sDummyFlipbook.finish = !sDummyFlipbook.finish; }

			ImGui::Text("Current Frame : %d / %d", sDummyFlipbook.curFrame + 1, sEditFlipbookData.frameCount);
			ImGui::TextUnformatted("Frame Adj");
			ImGui::SameLine();
			if (ImGui::ArrowButton("prev", ImGuiDir_Left)) { sDummyFlipbook.curFrame = (sDummyFlipbook.curFrame - 1 + sEditFlipbookData.frameCount) % sEditFlipbookData.frameCount; }
			ImGui::SameLine();
			if (ImGui::ArrowButton("next", ImGuiDir_Right)) { sDummyFlipbook.curFrame = (sDummyFlipbook.curFrame + 1) % sEditFlipbookData.frameCount; }

			if (ImGui::Button("Save"))
			{
				fb->Create(sEditFlipbookData);
			}

			ImGui::SameLine();

			if (ImGui::Button("Exit"))
			{
				if (fbData == sEditFlipbookData)
				{
					sEditBit = false;
				}
				else
				{
					ImGui::OpenPopup("Save Modal");
				}
			}

			if (ImGui::BeginPopupModal("Save Modal", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::TextUnformatted("Sprite data has been modified.");

				if (ImGui::Button("Save and Close"))
				{
					fb->Create(sEditFlipbookData);
					sEditBit = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				if (ImGui::Button("No save and Close"))
				{
					sEditFlipbookData = fbData;
					sEditBit = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				if (ImGui::Button("Cancel"))
				{
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
		else
		{
			ImGui::Text("Width : %dpx", fbData.width);
			ImGui::Text("Height : %dpx", fbData.height);
			ImGui::Text("Pivot Row : %d", fbData.pivotRow);
			ImGui::Text("Pivot Col : %d", fbData.pivotCol);
			ImGui::Text("Total Frame : %d", fbData.frameCount);
			ImGui::Text("Flip Speed : %.2f sec per frame", fbData.frameDuration);
			ImGui::Text("Loop : %s", fbData.loop ? "On" : "Off");

			if (ImGui::Button("Edit"))
			{
				sEditFlipbookData = fbData;
				sEditBit = true;
				sDummyFlipbook.Clear();
			}
		}
	}

	void EditorResourceViewer::ShowShaderSetDetail()
	{
		ShaderSet* ss = static_cast<ShaderSet*>(mTargetRes);

		ImGui::Text("Resource Name : %s", ss->GetName());
		ImGui::Text("Resource Type : %s", ShaderSet::sResourceString);
		ImGui::Text("Resource ID : %d", ss->GetID());
		ImGui::TextWrapped("Shader Path : %ls", ss->GetShaderFilePath());
		ImGui::Text("Shader Load Type : %s", ToString(ss->GetShaderLoadType()));
	}
}