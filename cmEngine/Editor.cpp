#include "EnginePch.h"
#include "Editor.h"
#include "EditorVoidPopup.h"
#include "EditorDebugViewer.h"
#include "EditorOverlay.h"
#include "EditorLogViewer.h"
#include "EditorSceneViewer.h"
#include "EditorResourceViewer.h"

namespace cmEngine
{
	template <typename Ty>
	static void ImGuiEditCallbackHelper(GameEntity& inGameEntity, const char* inHeaderName, const std::function<void(Ty*)>& inCallback)
	{
		if (Ty* comp = inGameEntity.TryFindComponent<Ty>())
		{
			if (ImGui::CollapsingHeader(inHeaderName, nullptr, ImGuiTreeNodeFlags_DefaultOpen))
			{
				// 삭제 버튼
				if (ImGui::BeginPopupContextItem())
				{
					if (ImGui::MenuItem("Delect")) { inGameEntity.RemoveComponent<Ty>(); }
					ImGui::EndPopup();
				}

				inCallback(comp);
			}
			ImGui::Spacing();
		}
	}

	//===================================================
	//			       Edit Callback
	//===================================================

	void DefaultEditCallback(GameEntity& inGameEntity)
	{
		ImGui::SeparatorText("ID");
		ImGui::Text("Entity ID : %d", inGameEntity.GetID());
		ImGui::Spacing();
	}

	void NameEditCallback(GameEntity& inGameEntity)
	{
		ImGuiEditCallbackHelper<Name>(inGameEntity, "Name##header", [](Name* name)
			{
				static char sNameBuffer[64];
				::strncpy_s(sNameBuffer, name->name.c_str(), sizeof(sNameBuffer) - 1);
				sNameBuffer[sizeof(sNameBuffer) - 1] = '\0';

				if (ImGui::InputText("Name", sNameBuffer, sizeof(sNameBuffer)))
				{
					name->name = sNameBuffer;
				}
			});
	}

	void TransformEditCallback(GameEntity& inGameEntity)
	{
		ImGuiEditCallbackHelper<Transform>(inGameEntity, "Transform##header", [](Transform* t)
			{
				// Position
				static float sPositionWeight = 0.001f;
				ImGui::BulletText("Position");
				ImGui::DragFloat("X##position", &t->position.x, sPositionWeight, -100.f, 100.f);
				ImGui::DragFloat("Y##position", &t->position.y, sPositionWeight, -100.f, 100.f);
				ImGui::DragFloat("Z##position", &t->position.z, sPositionWeight, -100.f, 100.f);
				if (ImGui::Button("Reset##Trans")) { t->position = Vector3::Zero; }
				ImGui::Separator();

				// Rotation
				float pitch = Math::RadToDeg(t->rotation.x);
				float yaw = Math::RadToDeg(t->rotation.y);
				float roll = Math::RadToDeg(t->rotation.z);

				static float sRotationWeight = 1.f;
				ImGui::BulletText("Rotation");
				ImGui::DragFloat("Pitch", &pitch, sRotationWeight, 0, 360, "%.3f", ImGuiSliderFlags_WrapAround);
				ImGui::DragFloat("Yaw", &yaw, sRotationWeight, 0, 360, "%.3f", ImGuiSliderFlags_WrapAround);
				ImGui::DragFloat("Roll", &roll, sRotationWeight, 0, 360, "%.3f", ImGuiSliderFlags_WrapAround);

				t->rotation.x = Math::DegToRad(pitch);
				t->rotation.y = Math::DegToRad(yaw);
				t->rotation.z = Math::DegToRad(roll);

				if (ImGui::Button("Reset##Rot")) { t->rotation = Vector3::Zero; }

				ImGui::Separator();

				// Scale
				static float sScaleWeight = 0.01f;
				ImGui::BulletText("Scale");
				ImGui::DragFloat("X##Scale", &t->scaling.x, sScaleWeight, 0.005f, 50.f);
				ImGui::DragFloat("Y##Scale", &t->scaling.y, sScaleWeight, 0.005f, 50.f);
				ImGui::DragFloat("Z##Scale", &t->scaling.z, sScaleWeight, 0.005f, 50.f);
				if (ImGui::Button("Reset##Scale")) { t->scaling = Vector3::One; }
			});
	}

	void CameraEditCallback(GameEntity& inGameEntity)
	{
		ImGuiEditCallbackHelper<Camera>(inGameEntity, "Camera##header", [&](Camera* cmr)
			{
				static int sCameraMode = static_cast<int>(cmr->mode);
				ImGui::RadioButton("Orthographic", &sCameraMode, 0);
				ImGui::RadioButton("Perspective", &sCameraMode, 1);

				cmr->mode = sCameraMode ? eCameraProjectionMode::Perspective : eCameraProjectionMode::Orthographic;

				ImGui::DragFloat("Near Plane", &cmr->nearPlane, 0.1f, 0.01f, 100.f);
				ImGui::DragFloat("Far Plane", &cmr->farPlane, 0.1f, 0.01f, 100.f);
				cmr->farPlane = max(cmr->farPlane, cmr->nearPlane + 0.1f);

				if (cmr->mode == eCameraProjectionMode::Orthographic)
				{
					ImGui::DragFloat("Width", &cmr->width, 0.1f, 0.01f, 100.f);
					ImGui::DragFloat("Height", &cmr->height, 0.1f, 0.01f, 100.f);

					if (ImGui::Button("Fit to viewport proportions"))
					{
						cmr->width = cmr->height * Renderer::GetAspectRatio();
					}
				}
				else
				{
					float fov = Math::RadToDeg(cmr->fov);
					ImGui::DragFloat("Fov", &fov, 1, 0.1f, 180.f);
					cmr->fov = Math::DegToRad(fov);
				}

				if (ImGui::Button("Set to main camera"))
				{
					SceneManager::GetCurrentScene()->SetMainCameraEntity(inGameEntity);
				}
			});
	}

	void FlipbookEditCallback(GameEntity& inGameEntity)
	{
		ImGuiEditCallbackHelper<FlipbookRender>(inGameEntity, "Flipbook##header", [](FlipbookRender* fbRender)
			{
				Flipbook* fb = fbRender->flipbook;
				const FlipbookData& fbData = fb->GetFlipbookData();

				// Flipbook Resource Data
				ImGui::SeparatorText("Flipbook Resource Data");
				if (ImGui::Button("Select Flipbook")){/* TODO */}
				ImGui::Spacing();

				ImGui::Text("Texture : %s", fbData.texture->GetName());
				ImGui::Text("Width : %dpx", fbData.width);
				ImGui::Text("Height : %dpx", fbData.height);
				ImGui::Text("Offset Row : %d", fbData.pivotRow);
				ImGui::Text("Offset Col : %d", fbData.pivotCol);
				ImGui::Text("Total Frame : %d", fbData.frameCount);
				ImGui::Text("Flip Speed : %.2f sec per frame", fbData.frameDuration);
				ImGui::Text("Loop : %s", fbData.loop ? "On" : "Off");

				// Flipbook Detailed Data
				ImGui::SeparatorText("Flipbook Detailed Data");
				ImGui::Text("Current Frame : %d / %d", fbRender->curFrame + 1, fbData.frameCount);

				// Flipbook frame adjust
				if (ImGui::ArrowButton("Prev Frame", ImGuiDir_Left)) { fbRender->curFrame = (fbRender->curFrame - 1 + fbData.frameCount) % fbData.frameCount; }
				ImGui::SameLine();
				if (ImGui::ArrowButton("Next Frame", ImGuiDir_Right)) { fbRender->curFrame = (fbRender->curFrame + 1) % fbData.frameCount; }
				if (ImGui::Button(fbRender->play ? "Stop" : "Play")) { fbRender->play = !fbRender->play; }
				ImGui::DragFloat("Playback speed", &fbRender->playbackSpeed, 0.01f, 0.01f, 32.f);
				ImGui::Text("Is Finished? : %s", fbRender->finish ? "Yes" : "No");
				if (ImGui::Button("Reset"))
				{
					fbRender->curFrame = 0;
					fbRender->playbackSpeed = 1.f;
					fbRender->finish = false;
				}
			});
	}

	void RenderProfileCallback(GameEntity& inGameEntity)
	{
		ImGuiEditCallbackHelper<RenderProfile>(inGameEntity, "RenderProfile##header", [](RenderProfile* inProfile)
			{
				// Shader
				ImGui::BulletText("Shader");
				if (ImGui::Button("Select ShaderSet")) {/* TODO */ }
				ImGui::Text("Shader Name : %s", inProfile->shaders->GetName());
				ImGui::Spacing();
				ImGui::Separator();

				// Render State
				const RenderState& state = inProfile->rendererState;
				ImGui::BulletText("RenderState");

				// Blend State
				ImGui::Combo("Blend State", (int*)(&state.blendState), RenderStatePool::sBlendStateString.data(), RenderStatePool::sBlendStateString.size());

				// Sampler State
				ImGui::Combo("Sampler State", (int*)(&state.samplerState), RenderStatePool::sSamplerStateString.data(), RenderStatePool::sSamplerStateString.size());

				// Depth Stencil State
				ImGui::Combo("Depth-Stencil State", (int*)(&state.depthStencilState), RenderStatePool::sDepthStencilStateString.data(), RenderStatePool::sDepthStencilStateString.size());

				// Rasterizer State
				ImGui::Combo("Rasterizer State", (int*)(&state.rasterizerState), RenderStatePool::sRasterizerStateString.data(), RenderStatePool::sRasterizerStateString.size());
			}
		);
	}
}

//===================================================
//					    Editor
//===================================================

namespace cmEngine
{
	void Editor::Initialize()
	{
		GuiRenderer::CreateConcreteGui<EditorDebugViewer>();
		GuiRenderer::CreateConcreteGui<EditorOverlay>();
		GuiRenderer::CreateConcreteGui<EditorLogViewer>();
		GuiRenderer::CreateConcreteGui<EditorSceneViewer>();
		GuiRenderer::CreateConcreteGui<EditorVoidPopup>();
		GuiRenderer::CreateConcreteGui<EditorResourceViewer>();

		AttachEditCallback<entt::entity>(DefaultEditCallback);
		AttachEditCallback<Name>(NameEditCallback);
		AttachEditCallback<Transform>(TransformEditCallback);
		AttachEditCallback<Camera>(CameraEditCallback);
		AttachEditCallback<FlipbookRender>(FlipbookEditCallback);
		AttachEditCallback<RenderProfile>(RenderProfileCallback);
	}
}
