#include "pch.h"
#include "Game.h"
#include "DemoScene.h"

void Game::Initialize()
{
	{
		ShaderSet* sh = ResourceManager::CreateResource<ShaderSet>("DemoShaderSet");
		VertexShader* vs = sh->GetVertexShader();
		vs->LoadHLSL(
			L"C:\\Users\\Ahnjiwoo\\Desktop\\Projects\\cmEngine\\CommonResource\\Shader\\1. SimpleColorShader.hlsli",
			"VS",
			"vs_5_0"
		);
		vs->Create<VertexPosColor>();
		vs->SetConstantBuffers<CBTransform, CBCamera>();

		PixelShader* ps = sh->GetPixelShader();
		ps->LoadHLSL(
			L"C:\\Users\\Ahnjiwoo\\Desktop\\Projects\\cmEngine\\CommonResource\\Shader\\1. SimpleColorShader.hlsli",
			"PS",
			"ps_5_0"
		);
		ps->Create();
	}

	SceneManager::CreateScene<DemoScene>();
	SceneManager::ChangeScene<DemoScene>();
}

void Game::CleanUp()
{
}
