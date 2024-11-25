#include "pch.h"
#include "Game.h"
#include "DemoScene.h"

void Game::Init()
{
	ShaderSet* sh = ResourceManager::Ref().CreateEmptyResource<ShaderSet>("TestShaders");
	sh->CreateByHLSL(
		L"C:\\Users\\Ahnjiwoo\\Desktop\\Projects\\cmEngine\\CommonResource\\Shader\\3. SimpleTexSpriteShader.hlsli",
		VertexPosTex::sInputElements,
		VertexPosTex::sInputElementsSize
	);

	SceneManager::Ref().CreateScene<DemoScene>();
	SceneManager::Ref().ChangeScene<DemoScene>();
}

void Game::Shutdown()
{
}
