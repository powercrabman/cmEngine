#include "0. cmEditor/cmEditor.h"
#include "1. EditorApp/EditorApp.h"

#include "10. Scene/SceneSerializer.h"

class PerformancePanel;

namespace cmEngine
{
	void EditorApp::Init()
	{
		EDITOR_CORE;

		// Texture
		std::filesystem::directory_iterator iter{ std::filesystem::current_path() / "Resources\\Texture" };
		for (auto entry : iter)
		{
			auto path = entry.path();
			auto ext = path.extension();
			if (ext == ".png" || ext == ".bmp")
			{
				auto name = path.filename().stem();
				Texture* tex = RESOURCE_MANAGER.CreateEmptyResource<Texture>(name.string());
				tex->LoadTextureImage(path.wstring());
			}
		}

		// Shader
		ShaderSet* ss = ResourceManager::Ref().CreateEmptyResource<ShaderSet>("Shader");
		ss->CreateByHLSL(L"C:\\Users\\Ahnjiwoo\\Desktop\\Projects\\cmEngine\\CommonResource\\Shader\\3. SimpleTexSpriteShader.hlsli", VertexPosTex::sInputElements, VertexPosTex::sInputElementsSize);

		// Sprite
		{
			Sprite* s     = ResourceManager::Ref().CreateEmptyResource<Sprite>("sp");
			SpriteData sd = {};
			sd.width      = 0; sd.height = 0;
			sd.pivotCol   = 0; sd.pivotRow = 0;
			sd.texture    = RESOURCE_MANAGER.TryFindResource<Texture>("ray");
			s->Create(sd);
		}

		{
			Sprite* s = ResourceManager::Ref().CreateEmptyResource<Sprite>("Player_Lookdown_Jump_Upper");
			SpriteData sd = {};
			sd.width = 0; sd.height = 0;
			sd.pivotCol = 0; sd.pivotRow = 0;
			sd.texture = RESOURCE_MANAGER.TryFindResource<Texture>("Player_Lookdown_Jump_Upper");
			s->Create(sd);
		}

		{
			Flipbook* fb = RESOURCE_MANAGER.CreateEmptyResource<Flipbook>("AlianFlipbook");
			FlipbookData d = {};
			d.width = 88;
			d.height = 78;
			d.frameCount = 16;
			d.frameDuration = 0.08f;
			d.loop = true;
			d.pivotCol = 0, d.pivotRow = 0;
			d.texture = RESOURCE_MANAGER.TryFindResource<Texture>("Alian_Idle");

			fb->Create(d);

			// Scene
			SceneSerializer{}.DeserializeSceneFromFile("EditorScene.json");
			Scene* sc = SCENE_MANAGER.TryFindScene("EditorScene");
		}
	}
}
