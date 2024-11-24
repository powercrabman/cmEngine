#include "pch.h"
#include "Game.h"
#include "DemoScene.h"

void Game::Initialize()
{
	{
		ShaderSet* sh = ResourceManager::CreateEmptyResource<ShaderSet>("TestShaders");
		sh->CreateByHLSL(
			L"C:\\Users\\Ahnjiwoo\\Desktop\\Projects\\cmEngine\\CommonResource\\Shader\\3. SimpleTexSpriteShader.hlsli",
			VertexPosTex::sInputElements,
			VertexPosTex::sInputElementsSize
		);
	}

	SceneManager::CreateScene<DemoScene>();
	SceneManager::ChangeScene<DemoScene>();
}

void Game::CleanUp()
{
}
